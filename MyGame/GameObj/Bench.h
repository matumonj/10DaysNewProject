#pragma once
#include"Object3d.h"
#include"Model.h"
#include<memory>
#include"Player.h"
#include"Sushi.h"
#include"Texture.h"
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
	bool DestroyChara;
	Player* player;
	Texture*SiTGauge;

	float EsitTime;
	float sitTime;
	bool LeaveF;
	bool SitChara;

	float Palpha=1.0f;
public:
	Bench();

	~Bench();

	void Initialize();
	void Update(std::vector<Sushi*> sushis);
	void Update2(std::vector<Sushi*>  sushis);
	void Update3(std::vector<Sushi*>  sushis);
	void UpdateS();
	void SitGaugeUp();
	void Draw();
	void SetChara();
	void SetCaharaCreate_P(bool f) { CharaCreate_P = f; }
	void SetCaharaCreate_C(bool f) { CharaCreate_C = f; }
void SetCaharaCreate_B(bool f) { CharaCreate_B = f; }
	void SetDestroyCahara(bool f) { DestroyChara = f; }
	void SetCharaSitF(bool f) { SitChara = f; }
	bool GetCharaSitF() { return SitChara; }
	bool GetLeaveF() { return LeaveF; }
	void SetLeaveF(bool f) { LeaveF = f; }
	
public:


	const XMFLOAT3& GetPosition() { return Position; }
	void SetPosition(const XMFLOAT3& position) { Position = position; }
	void SetRot(XMFLOAT3 rot) { Rot = rot; }
	const XMFLOAT3& GetRotation() { return Rot; }
private:
	std::unique_ptr<Object3d>BenchObj;

	XMFLOAT3 Position = {};
	XMFLOAT3 Scale = { 2,2,2 };
	XMFLOAT3 Rot={0,0,180};
	//ń]pAO
	//Ś®xNgšy²üčĢpxÅń]
	XMVECTOR move;

	XMMATRIX matRot;
private:
};






