#pragma once

#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include <DirectXMath.h>

/// <summary>
/// メッシュ衝突判定オブジェクト
/// </summary>
class MeshCollider :
	public BaseCollider
{
public:
	MeshCollider()
	{
		// メッシュ形状をセット
		shapeType = COLLISIONSHAPE_MESH;
	}

	/// <summary>
	/// 三角形の配列を構築する
	/// </summary>
	void ConstructTriangles(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;

	/// <summary>
	/// 球との当たり判定
	/// </summary>
	/// <param name="sphere">球</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	bool CheckCollisionSphere(const Sphere& sphere, DirectX::XMVECTOR* inter = nullptr, DirectX::XMVECTOR* reject = nullptr);

	/// <summary>
	/// レイとの当たり判定
	/// </summary>
	/// <param name="sphere">レイ</param>
	/// <param name="distance">距離（出力用）</param>
	/// <param name="inter">交点（出力用）</param>
	/// <returns>交差しているか否か</returns>
	bool CheckCollisionRay(const Ray& ray, float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

private:
	std::vector<Triangle> triangles;
	// ワールド行列の逆行列
	DirectX::XMMATRIX invMatWorld;
};

