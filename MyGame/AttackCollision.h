#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Input.h"
#include"CollisionPrimitive.h"
class AttackCollision
{
public:
	static AttackCollision* GetInstance();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
private:
	Box AttackArea;
	std::vector<Box> EnemyArea;
	Input* input;
	Object3d* cObj;
	Model* cModel;
	XMFLOAT3 Position;
public:
	void Init();

	void Update();

	void GetCol(int damage);
	void Draw();
};

