#pragma once
#include"Object3d.h"
#include"Model.h"
#include<memory>
class Rail {
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::šČŖ
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	Rail();

	~Rail();

	void Initialize();
	void Update();
	void Draw();
public:


	const XMFLOAT3& GetPosition() { return Position; }
	void SetPosition(const XMFLOAT3& position) { Position = position; }


private:
	std::unique_ptr<Object3d>RailObj;
	Model* RailModel;

	XMFLOAT3 Position = {0,-3,0};
	XMFLOAT3 Scale = { 1,1,1 };
	XMFLOAT3 Rot={0,-180,0};
	//ń]pAO
	//Ś®xNgšy²üčĢpxÅń]
	XMVECTOR move;

	XMMATRIX matRot;
private:
};

