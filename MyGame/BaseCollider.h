#pragma once

#include "CollisionTypes.h"
#include "CollisionInfo.h"
#include "Object3d.h"

/// <summary>
/// コライダー基底クラス
/// </summary>
class BaseCollider
{
public:
	friend class CollisionManager;

	inline void SetAttribute(unsigned short attribute) {
		this->attribute = attribute;
	}
	inline void AddAttribute(unsigned short attribute) {
		this->attribute |= attribute;
	}
	inline void RemoveAttribute(unsigned short attribute) {
		this->attribute &= !attribute;
	}

protected:
	//当たり判定属性
	unsigned short attribute = 0b1111111111111111;

public:
	BaseCollider() = default;
	virtual ~BaseCollider() = default;

	inline void SetObject(Object3d* object) {
		this->object3d = object;
	}

	inline Object3d* GetObject3d() {
		return object3d;
	}

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;

	inline CollisionShapeType GetShapeType() { return shapeType; }

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	/// <param name="info">衝突情報</param>
	inline void OnCollision(const CollisionInfo& info) {
		object3d->OnCollision(info);
	}

protected:
	Object3d* object3d = nullptr;
	// 形状タイプ
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
};

