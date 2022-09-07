#pragma once

#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <string>

/// <summary>
/// マテリアル
/// </summary>
class Material
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		XMFLOAT3 ambient; // アンビエント係数
		float pad1; // パディング
		XMFLOAT3 diffuse; // ディフューズ係数
		float pad2; // パディング
		XMFLOAT3 specular; // スペキュラー係数
		float alpha;	// アルファ
	};

public: // 静的メンバ関数

	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	static void StaticInitialize();

	/// <summary>
	/// マテリアル生成
	/// </summary>
	/// <returns>生成されたマテリアル</returns>
	static Material* Create();

private: // 静的メンバ変数
	// デバイス
	static ComPtr<ID3D12Device> device;
	static ComPtr<ID3D12GraphicsCommandList> cmdList;
public:
	std::string name;	// マテリアル名
	XMFLOAT3 ambient;	// アンビエント影響度
	XMFLOAT3 diffuse;	// ディフューズ影響度
	XMFLOAT3 specular;	// スペキュラー影響度
	float alpha;		// アルファ
	std::string textureFilename;	// テクスチャファイル名

public:
	/// <summary>
	/// 定数バッファの取得
	/// </summary>
	/// <returns></returns>
	ID3D12Resource* GetConstantBuffer() { return constBuff.Get(); }

	/// テクスチャ読み込み
	/// </summary>
	/// <param name="directoryPath">読み込みディレクトリパス</param>
	/// <param name="cpuHandle">CPUデスクリプタハンドル</param>
	/// <param name="gpuHandle">GPUデスクリプタハンドル</param>
	void LoadTexture(const std::string& directoryPath, CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle, CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	const CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCpuHandle() { return cpuDescHandleSRV; }
	const CD3DX12_GPU_DESCRIPTOR_HANDLE& GetGpuHandle() { return gpuDescHandleSRV; }

private:
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

private:
	// コンストラクタ
	Material() {
		ambient = { 0.3f, 0.3f, 0.3f };
		diffuse = { 0.0f, 0.0f, 0.0f };
		specular = { 0.0f, 0.0f, 0.0f };
		alpha = 1.0f;
	}

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファの生成
	/// </summary>
	void CreateConstantBuffer();
};

