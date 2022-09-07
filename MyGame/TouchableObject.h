#pragma once
#include "Object3d.h"
class TouchableObject :
	public Object3d
{
private: // エイリアス
// Microsoft::WRL::を省略
	//template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// オブジェクト生成
	/// </summary>
	/// <returns></returns>
	static TouchableObject* Create(Model* model, DebugCamera* camera);

	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	bool Initialize(Model* model,  DebugCamera* camera);

	/// <summary>
	/// スケールの設定
	/// </summary>
	/// <param name="position">スケール</param>
	inline void SetScale(float scale) { this->scale = { scale,scale,scale }; }
	//void SetScale(XMFLOAT3 scale) = delete;
};

