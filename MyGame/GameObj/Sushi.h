#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Texture.h"
#include<memory>
class Sushi
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
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
	//回転運動
	void Moves();
	//復活処理
	void Rebirth(int cooltime);

	void RotState();

	void TexSet();
	void TexUp();
	void TexDraw();
public:
	enum SushiMove {
		GATE,//入場
		LANE,//レーン回る
		DUMP,//廃棄,
		CREATE
	};
protected:
	std::unique_ptr<Object3d>SushiObj;
	Model* SushiModel;
	Texture* HPTex;
	XMFLOAT3 Position=GatePos;
	XMFLOAT3 Scale={2,2,2};
	XMFLOAT3 Rot;
	//回転用アングル
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	SushiMove SMove;

	int HP;
	int MaxHP;

	int coolTime;
	//ゴミ箱
	const XMFLOAT3 GarbagepPos = { 20,0,-10 };
	//ゲート
	const XMFLOAT3 GatePos = { 0,0,-30 };
private:
	
	bool isDump;
	bool isStart;
};

