#pragma once
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

class OBB
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	XMVECTOR m_Pos;              // 位置
	XMVECTOR m_NormaDirect[3];   // 方向ベクトル 回転ベクトル打ち込む
	float m_fLength[3];             // 各軸方向の長さ

public:
	XMVECTOR GetDirect(int elem) { return m_NormaDirect[elem]; }   // 指定軸番号の方向ベクトルを取得
	float GetLen_W(int elem) { return m_fLength[elem]; }          // 指定軸方向の長さを取得
	XMVECTOR GetPos_W() { return m_Pos; }
};