#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Texture.h"
#include<memory>
class Sushi
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	virtual ~Sushi();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw()=0;
	//âÒì]â^ìÆ
	void Moves(int cooltime);
	
	void RotState();

	void TexSet();
	void TexUp();
	void TexDraw();
public:
	enum SushiMove {
		GATE,//ì¸èÍ
		LANE,//ÉåÅ[ÉìâÒÇÈ
		DUMP,//îpä¸,
		CREATE,
		DEAD
	};
protected:
	std::unique_ptr<Object3d>SushiObj;
	Model* SushiModel;
	Texture* HPTex;
protected:
	XMFLOAT3 Position=GatePos;
	XMFLOAT3 Scale={2,2,2};
	XMFLOAT3 Rot;
	//âÒì]ópÉAÉìÉOÉã
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	SushiMove SMove;

	int HP;
	int MaxHP;

	int coolTime;
	//ÉSÉ~î†
	const XMFLOAT3 GarbagepPos = { -5,0,5 };
	//ÉQÅ[Ég
	const XMFLOAT3 GatePos = { 0,0,-10 };
private:
	bool CoolEnd;
	bool isDump;
	bool isStart;
};

