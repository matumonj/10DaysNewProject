#pragma once
#include"Object3d.h"
#include"Model.h"
#include<memory>
class Bench {
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::šČŖ
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	Bench();

	~Bench();

	void Initialize();
	void Update();
	void Draw();

public:
private:
	std::unique_ptr<Object3d>BenchObj;
	Model* BenchModel;

	XMFLOAT3 Position = {};
	XMFLOAT3 Scale = { 2,2,2 };
	XMFLOAT3 Rot;
	//ń]pAO
	//Ś®xNgšy²üčĢpxÅń]
	XMVECTOR move;

	XMMATRIX matRot;
private:
};






