#pragma once
#include"WinApp.h"
#include"HUD.h"
class HUDLayOut
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	static HUDLayOut* GetInstance();
	void ChangePosition_PlayerHP();

	void Update();
	void NowOperation();

	void SetLayOutMode(bool f) { LayOutMode = f; }
	bool GetLayOutMode() { return LayOutMode; }
private:
	enum Operation{
		None,
		PLAYERHP,
		ENEMYHP,
		Skill,
	};
	XMFLOAT2 center= { 1050,500 };
	Operation operation = None;
	POINT p;
	bool LayOutMode;
	int count = 0;
	float x;
	bool f;
	float y;
};

