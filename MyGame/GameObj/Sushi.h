#pragma once
#include"Object3d.h"
#include"Model.h"
#include"Texture.h"
#include"ScoreMgr.h"
#include<memory>
#include <Base/Audio.h>

class Sushi
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::???ȗ?
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	virtual ~Sushi();

	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void TitleUpda() = 0;
	virtual void Draw()=0;
public:
	enum Wave {
		WAVE1or2,
		WAVE3
	};
	Wave wave;
	Wave GetWave() { return wave; }

	//???]?^??
	void TexSet();
	void TexUp();
	void TexDraw();
public:
	XMFLOAT3 GetPos() { return Position; }
	void SetPos(XMFLOAT3 Pos) { Position = Pos; }
	XMFLOAT3 GetRot() { return Rot; }
	void SetRot(XMFLOAT3 rot) { Rot = rot; }
	void SetScale(XMFLOAT3 scale) { Scale = scale; }
	XMFLOAT3 GetScale() { return Scale; }
protected:
	std::unique_ptr<Object3d>SushiObj;
	Model* SushiModel;
	Texture* HPTex;
protected:
	XMFLOAT3 Position;
	XMFLOAT3 Scale={2,2,2};
	XMFLOAT3 Rot;
	//???]?p?A???O??
	XMVECTOR move;

	int HP;
	int MaxHP;
	bool isDead;
	bool isEaten;
	int coolTime;
	int ScorePoint;
public:
	int GetHP() { return HP; }
	void SetDead(bool f) { isDead = f; }
	void SetEaten(bool f) { isEaten = f; }
	bool GetDead() { return isDead; }
	bool GetEaten() { return isEaten; }

	void RecvDamage(int Damage) { HP = HP - Damage; }
	int GetScorepoint() { return ScorePoint; }
private:
	bool CoolEnd;
	bool isDump;
	bool isStart;
};

