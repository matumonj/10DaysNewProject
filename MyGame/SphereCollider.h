#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

/// <summary>
/// 球衝突判定オブジェクト
/// </summary>
class SphereCollider : public BaseCollider, public Sphere
{
private: // エイリアス
	// DirectX::を省略
	using XMVECTOR = DirectX::XMVECTOR;
public:
	SphereCollider(XMVECTOR offset = { 0,0,0,0 }, float radius = 1.0f) :
		offset(offset),
		radius(radius)
	{
		// 球形状をセット
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	// オブジェクト中心からのオフセット
	XMVECTOR offset;
	// 半径
	float radius;
public:
	inline const XMVECTOR& GetOffset() { return offset; }
	inline void SetOffset(const XMVECTOR& offset) { this->offset = offset; }
	inline float GetRadius() { return radius; }
};

