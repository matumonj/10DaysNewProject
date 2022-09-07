#pragma once
/// <summary>
/// 当たり判定プリミティブ
/// </summary>

#include <DirectXMath.h>

/// <summary>
/// 球
/// </summary>
struct Sphere
{
	// 中心座標
	DirectX::XMVECTOR center = {};
	// 半径
	float radius = 1.0f;
};

/// <summary>
/// 平面
/// </summary>
struct Plane
{
	// 法線ベクトル
	DirectX::XMVECTOR normal = { 0,1,0 };
	// 原点(0,0,0)からの距離
	float distance = 0.0f;
};

/// <summary>
/// 法線付き三角形（時計回りが表面）
/// </summary>
class Triangle
{
public:
	// 頂点座標3つ
	DirectX::XMVECTOR	p0;
	DirectX::XMVECTOR	p1;
	DirectX::XMVECTOR	p2;
	// 法線ベクトル
	DirectX::XMVECTOR	normal;

	/// <summary>
	/// 法線の計算
	/// </summary>
	void ComputeNormal();
};

/// <summary>
/// レイ（半直線）
/// </summary>
struct Ray
{
	// 始点座標
	DirectX::XMVECTOR	start = { 0,0,0,1 };
	// 方向
	DirectX::XMVECTOR	dir = { 1,0,0,0 };
};

struct AABB
{

};

struct Box
{
	DirectX::XMFLOAT2 position;
	DirectX::XMFLOAT2 scale;
};

struct Point
{
	float x;
	float y;
};