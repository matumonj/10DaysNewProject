#pragma once
#include"Texture.h"
#include"Input.h"
class HalfAttack
{
public:
	~HalfAttack();
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
private:
	enum AttackArea {
		LEFT,
		RIGHT
	};
	AttackArea Area;

	Texture* HalfAreaTex;
	float RotY;
	bool fase1, fase2,fase3,fase4;
	int AttackCount;
	float TexAlpha = 1.0f;
	float AfterPositionZ;
	float BeforePositionZ;
	float KnockTime = 0.0f;

	 XMFLOAT3 CenterPos;
	//fase1　カウントダウンと中央に戻る処理
	XMFLOAT3 PlayerPos;
	XMFLOAT3 BossEnemyPos;

public:enum Fase {
	FASENON,
	FASEONE,
	FASETWO,
	FASETHREE,
	FASEFOUR
};
private:
	  Fase fase;
public:
	static HalfAttack* GetInstance();
	XMFLOAT3 MoveCenterPos();
	void Initialize();
	void Draw();
	void ActionJudg();
	void TurnCenter();

	void SetAttackFase(bool f) { if (f && fase!=FASEONE) { fase = FASEONE; } }
	Fase GetFaseEnd() { return fase; }
};

