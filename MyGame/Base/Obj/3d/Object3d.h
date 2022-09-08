#pragma once

#include<string>
#include"Model.h"
#include"LightGroup.h"
#include"CollisionInfo.h"
#include"DebugCamera.h"
//#include"CollisionManager.h"
class BaseCollider;

class Object3d
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	Model* model = nullptr;

	static Camera* camera;
public: // サブクラス
	void SetModel(Model* model) { this->model = model; }

	//定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		XMFLOAT4 color;
		//XMMATRIX mat;
		// 定数バッファ用データ構造体B0
		XMMATRIX viewproj;    // ビュープロジェクション行列
		XMMATRIX world; // ワールド行列
		XMFLOAT3 cameraPos; // カメラ座標（ワールド座標）
		float ks;
		bool gsflag;
		XMFLOAT3 ks2;
		bool f;
	};

private: // 定数
	XMFLOAT3 FogCenter;
	static const int division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const int planeCount = division * 2 + division * 2;		// 面の数
	static const int vertexCount = planeCount * 3;		// 頂点数

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	/// <returns>成否</returns>
	static bool StaticInitialize(int window_width, int window_height, Camera* camera = nullptr);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create(DebugCamera* camera);

	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// ベクトルによる移動
	/// </summary>
	/// <param name="move">移動量</param>
	static void CameraMoveVector(XMFLOAT3 move);

private: // 静的メンバ変数
	// デバイス
	static ComPtr<ID3D12Device> device;

	// コマンドリスト
	static ComPtr<ID3D12GraphicsCommandList> cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;



	// ビュー行列
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;

	// 頂点データ配列

	//static unsigned short indices[planeCount * 3];

private:// 静的メンバ関数

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static bool InitializeGraphicsPipeline();

	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	/// <returns>成否</returns>

	/// <summary>
	/// モデル作成
	/// </summary>


	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

	static void UpdateViewMatrix(XMMATRIX mat);

public: // メンバ関数
	Object3d() = default;

	virtual ~Object3d();

	virtual bool Initialize( DebugCamera* camera);
	//void CreateModel();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update(XMFLOAT4 color, DebugCamera* camera);

	virtual void Update(XMMATRIX matWorld, XMFLOAT4 color, DebugCamera* camera);

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	/// <summary>
	/// 座標の取得
	/// </summary>
	/// <returns>座標</returns>
	void SetFogCenter(XMFLOAT3 pos) { FogCenter = pos; }
	const XMFLOAT3& GetPosition() { return position; }
	const XMFLOAT3& GetRotation() { return rotation; }
	const XMFLOAT3& GetScale() { return scale; }
	/// <summary>
	/// ワールド行列の取得
	/// </summary>
	/// <returns>ワールド行列</returns>
	const XMMATRIX& GetMatWorld() { return matWorld; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void SetRotation(XMFLOAT3 rotation) { this->rotation = rotation; }
	void SetScale(XMFLOAT3 scale) { this->scale = scale; }

	static void SetCamera(Camera* camera) {
		Object3d::camera = camera;
	}

	static void SetLightGroup(LightGroup* lightGroup) {
		Object3d::lightGroup = lightGroup;
	}
	static LightGroup* lightGroup;
protected: // メンバ変数
	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };

	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
	bool rf;
	bool gsf;
	XMMATRIX rm,rt,rr,rs;
	bool setef=false;
public:
	void setFog(bool f) { setef = f; }
	void setr(bool f) { rf = f; }
	XMMATRIX GetMatrot() {return matRot; }
	XMMATRIX GetMatScl() { return matScale; }
	void SetRotS(XMMATRIX matrot) { matRot *= matrot; }
	void Setf(bool flag);
	XMMATRIX GetMatTrans() { return matTrans; }
	void SetMatrot(XMMATRIX rot) { rm = rot; }
	void SetMatRot(XMMATRIX rot) { rt = rot; }
	void SetMatTrans(XMMATRIX rot) { rt = rot; }
	void SetMatScale(XMMATRIX rot) { rs = rot; }
	void UpdateWorldMatrix();
	void UpdateWorldMatrix(XMMATRIX mat);
	void SetCollider(BaseCollider* collider);
	virtual void OnCollision(const CollisionInfo& info) {}
	void SetParent(XMMATRIX matworld) { this->matWorld *= matworld; }
	void SetColor(XMFLOAT4 color) { this->color = color; }
protected:
	const char* name = nullptr;
	public:

	BaseCollider* collider = nullptr;
	private:
		XMMATRIX matScale, matRot, matTrans;
		XMFLOAT2 time;
public:
	/// <summary>
	/// モデルを取得
	/// </summary>
	/// <param name="material">マテリアル</param>
	inline Model* GetModel() { return model; }
};



