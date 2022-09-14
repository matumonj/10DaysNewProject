#pragma once
#include"Object3d.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include "FbxLoader.h"
#include"DirectXCommon.h"
#include"f_Model.h"
#include"f_Object3d.h"
#include"ObjectManager.h"
#include"Input.h"
#include"Sprite.h"
#include"Sushi.h"
class Player {
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	virtual ~Player();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void IconDraw() = 0;
	virtual void Attack(std::vector<Sushi*>sushis) = 0;
	virtual void Attack2(std::vector<Sushi*>sushis) = 0;
	virtual void Attack3(std::vector<Sushi*> sushis) = 0;
	
	void AttackJudg(std::vector<Sushi*>sushis);

	void AttackJudg2(std::vector<Sushi*> sushis);

	void AttackJudg3(std::vector<Sushi*>sushis);
public:
	enum PlayerMove {
	WAIT,//待機
	EATING,//攻撃中
	};
	enum CharaTag {
		TPLAYER,
		TCAT,
		TBIRD
	};
	XMFLOAT3 GetPos() { return Position; }
	PlayerMove GetState() { return SMove; }
	void SetPosition(XMFLOAT3 pos) { Position = pos; }
	Sprite* GetSprite() { return iconSprite; }
	void SetRot(XMFLOAT3 rot) { m_fbxObject->SetRotation(rot); }
	CharaTag GetCharaTag() { return ctag; }
	void SetColor(XMFLOAT4 color) { m_fbxObject->SetColor(color); }
	void EatAction(std::vector<Sushi*> sushis);
protected:
	CharaTag ctag;
	Sprite* iconSprite;
	std::unique_ptr<f_Object3d>m_fbxObject;
	float f_time;
	//プレイヤーから寿司に対してのアプロ
	int Damage;
	float AtkCool;
	float Range;

	bool AtkFlag;
	bool AtkFlag2;
	bool AtkFlag3;
protected:
	XMFLOAT3 Position = {0,0,5};
	XMFLOAT3 Scale = { 1,1,1 };
	XMFLOAT3 Rot;
	//回転用アングル
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	PlayerMove SMove;

	int HP;
	int MaxHP;

	int coolTime;
	float CoolTime;
	bool Cool;
private:
	bool CoolEnd;
	bool isDump;
	bool isStart;
};
