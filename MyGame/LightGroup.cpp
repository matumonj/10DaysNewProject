#include "LightGroup.h"
#include <assert.h>
#include"DirectXCommon.h"
using namespace DirectX;

/// <summary>
/// 静的メンバ変数の実体
/// </summary>
ComPtr<ID3D12Device> LightGroup::device = nullptr;

ComPtr<ID3D12GraphicsCommandList>LightGroup::cmdList=nullptr;

void LightGroup::StaticInitialize()
{

	LightGroup::device = DirectXCommon::GetInstance()->GetDev();
	LightGroup::cmdList = DirectXCommon::GetInstance()->GetCmdList();
	
	
}

LightGroup* LightGroup::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	LightGroup* instance = new LightGroup();

	// 初期化
	instance->Initialize();

	return instance;
}

void LightGroup::Initialize()
{
	// nullptrチェック
	assert(device);

	DefaultLightSetting();

	HRESULT result;
	// 定数バッファの生成
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	// アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	if (FAILED(result)) {
		assert(0);
	}

	// 定数バッファへデータ転送
	TransferConstBuffer();
}

void LightGroup::Update()
{
	// 値の更新があった時だけ定数バッファに転送する
	if (dirty) {
		TransferConstBuffer();
		dirty = false;
	}
}

void LightGroup::Draw( UINT rootParameterIndex)
{
	// 定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex, constBuff->GetGPUVirtualAddress());
}

//void LightGroup::TransferConstBuffer()
//{
//	HRESULT result;
//	// 定数バッファへデータ転送
//	ConstBufferData* constMap = nullptr;
//	result = constBuff->Map(0, nullptr, (void**)&constMap);
//	if (SUCCEEDED(result)) {
//		// 環境光
//		constMap->ambientColor = ambientColor;
//		// 平行光源
//		for (int i = 0; i < DirLightNum; i++) {
//			// ライトが有効なら設定を転送
//			if (dirLights[i].IsActive()) {
//				constMap->dirLights[i].active = 1;
//				constMap->dirLights[i].lightv = -dirLights[i].GetLightDir();
//				constMap->dirLights[i].lightcolor = dirLights[i].GetLightColor();
//			}
//			// ライトが無効ならライト色を0に
//			else {
//				constMap->dirLights[i].active = 0;
//			}
//		}
//		// 点光源
//		for (int i = 0; i < PointLightNum; i++) {
//			// ライトが有効なら設定を転送
//			if (pointLights[i].IsActive()) {
//				constMap->pointLights[i].active = 1;
//				constMap->pointLights[i].lightpos = pointLights[i].GetLightPos();
//				constMap->pointLights[i].lightcolor = pointLights[i].GetLightColor();
//				constMap->pointLights[i].lightatten = pointLights[i].GetLightAtten();
//			}
//			// ライトが無効ならライト色を0に
//			else {
//				constMap->pointLights[i].active = 0;
//			}
//		}
//		constBuff->Unmap(0, nullptr);
//	}
//}
void LightGroup::TransferConstBuffer()
{
	HRESULT result;
	// 定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		// 環境光
		constMap->ambientColor = ambientColor;
		// 平行光源
		for (int i = 0; i < DirLightNum; i++) {
			// ライトが有効なら設定を転送
			if (dirLights[i].IsActive()) {
				constMap->dirLights[i].active = 1;
				constMap->dirLights[i].lightv = -dirLights[i].GetLightDir();
				constMap->dirLights[i].lightcolor = dirLights[i].GetLightColor();
			}
			// ライトが無効ならライト色を0に
			else {
				constMap->dirLights[i].active = 0;
			}
		}
		// 点光源
		for (int i = 0; i < PointLightNum; i++) {
			// ライトが有効なら設定を転送
			if (pointLights[i].IsActive()) {
				constMap->pointLights[i].active = 1;
				constMap->pointLights[i].lightpos = pointLights[i].GetLightPos();
				constMap->pointLights[i].lightcolor = pointLights[i].GetLightColor();
				constMap->pointLights[i].lightatten = pointLights[i].GetLightAtten();
			}
			// ライトが無効ならライト色を0に
			else {
				constMap->pointLights[i].active = 0;
			}
		}
		// スポットライト
		for (int i = 0; i < SpotLightNum; i++) {
			// ライトが有効なら設定を転送
			if (spotLights[i].IsActive()) {
				constMap->spotLights[i].active = 1;
				constMap->spotLights[i].lightv = -spotLights[i].GetLightDir();
				constMap->spotLights[i].lightpos = spotLights[i].GetLightPos();
				constMap->spotLights[i].lightcolor = spotLights[i].GetLightColor();
				constMap->spotLights[i].lightatten = spotLights[i].GetLightAtten();
				constMap->spotLights[i].lightfactoranglecos = spotLights[i].GetLightFactorAngleCos();
			}
			// ライトが無効ならライト色を0に
			else {
				constMap->spotLights[i].active = 0;
			}
		}
		constBuff->Unmap(0, nullptr);
	}
}
void LightGroup::DefaultLightSetting()
{
	dirLights[0].SetActive(true);
	dirLights[0].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights[0].SetLightDir({ 0.0f, -1.0f, 0.0f, 0 });

	dirLights[1].SetActive(true);
	dirLights[1].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights[1].SetLightDir({ +0.5f, +0.1f, +0.2f, 0 });

	dirLights[2].SetActive(true);
	dirLights[2].SetLightColor({ 1.0f, 1.0f, 1.0f });
	dirLights[2].SetLightDir({ -0.5f, +0.1f, -0.2f, 0 });
}

void LightGroup::SetAmbientColor(const XMFLOAT3& color)
{
	ambientColor = color;
	dirty = true;
}

void LightGroup::SetDirLightActive(int index, bool active)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetActive(active);
}

void LightGroup::SetDirLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetLightDir(lightdir);
	dirty = true;
}

void LightGroup::SetDirLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < DirLightNum);

	dirLights[index].SetLightColor(lightcolor);
	dirty = true;
}
///点光源//////////////////////////
void LightGroup::SetPointLightActive(int index, bool active)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetActive(active);
}

void LightGroup::SetPointLightPos(int index, const XMFLOAT3& lightpos)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightPos(lightpos);
	dirty = true;
}

void LightGroup::SetPointLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightColor(lightcolor);
	dirty = true;
}

void LightGroup::SetPointLightAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < PointLightNum);

	pointLights[index].SetLightAtten(lightAtten);
	dirty = true;
}
////////////////////////////////////////

//スポットライト/////////////////////////
void LightGroup::SetSpotLightActive(int index, bool active)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetActive(active);
}

void LightGroup::SetSpotLightDir(int index, const XMVECTOR& lightdir)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightDir(lightdir);
	dirty = true;
}

void LightGroup::SetSpotLightPos(int index, const XMFLOAT3& lightpos)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightPos(lightpos);
	dirty = true;
}

void LightGroup::SetSpotLightColor(int index, const XMFLOAT3& lightcolor)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightColor(lightcolor);
	dirty = true;
}

void LightGroup::SetSpotLightAtten(int index, const XMFLOAT3& lightAtten)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightAtten(lightAtten);
	dirty = true;
}

void LightGroup::SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle)
{
	assert(0 <= index && index < SpotLightNum);

	spotLights[index].SetLightFactorAngle(lightFactorAngle);
	dirty = true;
}

void LightGroup::LightSetting()
{
	SetDirLightActive(0, false);
	SetDirLightActive(1, false);
	SetDirLightActive(2, false);
	SetPointLightActive(0, true);
	//pointLightPos[0] = 0.0f;
	//pointLightPos[1] = 1.0f;
	//pointLightPos[2] = 0.0f;
	SetPointLightActive(0, false);
	SetPointLightActive(1, false);
	SetPointLightActive(2, false);
	SetSpotLightActive(0, true);
}

void LightGroup::SpotLightUpdate()
{
	{//ライトのパラメータを反映 	
		SetSpotLightDir(0, XMVECTOR({ spotLightDir[0],spotLightDir[1],spotLightDir[2],0 }));
		SetSpotLightPos(0, XMFLOAT3(spotLightpos));
		SetSpotLightColor(0, XMFLOAT3(spotLightColor));
		SetSpotLightAtten(0, XMFLOAT3(spotLightAtten));
		SetSpotLightFactorAngle(0, XMFLOAT2(spotLightFactorAngle));
	}
	Update();
}
////////////////////////////////////