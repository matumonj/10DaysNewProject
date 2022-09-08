#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>

class Sprite
{
private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


public:
	//Sprite();
	//スプライト用
	struct VertexPosUv
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};
	//定数バッファ用
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列

	};
	
	static bool StaticInitialize(int window_width, int window_height);
	static bool LoadTexture(UINT texnumber, const wchar_t* filename);
	static void PreDraw();
	static void PostDraw();
	static Sprite* Create(UINT texNumber, XMFLOAT2 position, XMFLOAT4 color = { 1, 1, 1, 1 }, XMFLOAT2 anchorpoint = { 0.0f, 0.0f });
protected:
	// テクスチャの最大枚数
	static const int srvCount = 512;
	// 頂点数
	static const int vertNum = 4;
	// デバイス
	static ComPtr<ID3D12Device> device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ComPtr<ID3D12GraphicsCommandList> cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;
	// 射影行列
	static XMMATRIX matProjection;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texBuff[srvCount];
public:
	//コンストラクタ
	Sprite();
	Sprite(UINT texNumber, XMFLOAT2 position, XMFLOAT2 size, XMFLOAT4 color, XMFLOAT2 anchorpoint);
	//初期化
	bool Initialize();

	//角度の設定
	void SetRotation(float rotation);

	//座標の取得
	const XMFLOAT2& GetPosition() { return position; }

	//座標の設定
	void SetPosition(XMFLOAT2 position);

	//サイズの設定
	void SetSize(XMFLOAT2 size);

	//アンカーポイントの設定
	void SetAnchorPoint(XMFLOAT2 anchorpoint);

	//テクスチャ範囲設定
	void SetTextureRect(XMFLOAT2 texBase, XMFLOAT2 texSize);
	void SpriteUpdate(XMMATRIX matview, XMMATRIX matprojection, XMFLOAT4 color);
	//描画
	void Draw();
	void feed(float& feed);
protected:
	bool CollisionCursul;
	int setf = 0;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// テクスチャ番号
	UINT texNumber = 0;
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	XMFLOAT2 position{};
	// スプライト幅、高さ
	XMFLOAT2 size = { 100.0f, 100.0f };
	// アンカーポイント
	XMFLOAT2 anchorpoint = { 0, 0 };
	// ワールド行列
	XMMATRIX matWorld{};
	// 色
	XMFLOAT4 color;
	// テクスチャ始点
	XMFLOAT2 texBase = { 0, 0 };
	// テクスチャ幅、高さ
	XMFLOAT2 texSize = { 100.0f, 100.0f };
bool f;
public:
	void SetHUDLayOutFlag(bool flag) { f = flag; }
	bool GetHUDLayOutFlag() { return f; }
	void Setfeed(int set) { this->setf = set; }
	void setcolor(XMFLOAT4 color){ this->color = color; }

	void TransferVertices();
	XMFLOAT2 GetSize() { return size; }
	void ChangePosition_PlayerHP(XMFLOAT2 MousePosition);
	void ChangePosition(XMFLOAT2 MousePosition,XMFLOAT2 &c);
};
