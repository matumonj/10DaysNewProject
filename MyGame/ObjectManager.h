#pragma once
#include"Object3d.h"
#include"Model.h"
#include"f_Object3d.h"
#include"f_Model.h"
#include"DebugCamera.h"
#include<memory>
class ObjectManager
{
public:
	virtual ~ObjectManager();
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	virtual void SetCollider();

	virtual void Initialize(DebugCamera*camera) = 0;

	virtual void ParameterSet_Obj(DebugCamera* camera);
	virtual void ParameterSet_Fbx(DebugCamera* camera);

	virtual void Update(DebugCamera*camera)=0;

	virtual void Draw_Obj();
	virtual void Draw_Fbx();

	virtual void Draw() = 0;
	virtual void CollisionField(DebugCamera* camera);

protected:
	std::unique_ptr<Object3d> m_Object;
	Model* m_Model;

	std::unique_ptr<f_Object3d> m_fbxObject;
	f_Model* m_fbxModel;

	XMFLOAT3 Position;
	XMFLOAT3 Rotation;
	XMFLOAT3 Scale;
	XMFLOAT4 Color;
	//接地フラグ
	bool onGround = true;
	//落下ベクトル
	XMVECTOR fallV;
	float radius_adjustment;
public:
	XMFLOAT3 GetPosition() { return Position;}
	XMFLOAT3 GetRotation() { return Rotation; }
	XMFLOAT3 GetScale() { return Scale; }
	void SetPosition(XMFLOAT3 position) { Position = position; }
	void SetRotation(XMFLOAT3 rotation) { Rotation = rotation; }
	void SetScale(XMFLOAT3 scale) { Scale = scale; }
	void SetColor(XMFLOAT4 color) { Color = color; }
};

