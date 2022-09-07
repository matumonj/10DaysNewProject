#pragma once
#include"Object3d.h"
#include"Model.h"
#include"SphereCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"
using namespace DirectX;

class FieldCollision:public Object3d
{
private:
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	//生き死のフラグ
	bool AliveFlag = TRUE;
	//体力
	float HP;

protected:
	//接地フラグ
	bool onGround = true;
	//落下ベクトル
	XMVECTOR fallV;
public:
	
};

