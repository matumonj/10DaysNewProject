#pragma once
#include"Object3d.h"
#include"Model.h"
#include<memory>
#include"Player.h"
#include"Sushi.h"
class Bench {
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::šČŖ
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	bool CharaCreate_P;
	bool CharaCreate_C;
	bool CharaCreate_D;
	bool CharaCreate_B;
	Player* player;
public:
	Bench();

	~Bench();

	void Initialize();
	void Update(Sushi*sushis);
	void Draw();
	void SetChara();
	void SetCaharaCreate_P(bool f) { CharaCreate_P = f; }
	void SetCaharaCreate_C(bool f) { CharaCreate_C = f; }
	void SetCaharaCreate_D(bool f) { CharaCreate_D = f; }
	void SetCaharaCreate_B(bool f) { CharaCreate_B = f; }
public:


	const XMFLOAT3& GetPosition() { return Position; }
	void SetPosition(const XMFLOAT3& position) { Position = position; }


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






