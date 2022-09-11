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
class Player {
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
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
public:
	enum PlayerMove {
	WAIT,//�ҋ@
	EATING,//�U����
	};
	enum CharaTag {
		TPLAYER,
		TCAT,
		TDOG,
		TBIRD
	};
	XMFLOAT3 GetPos() { return Position; }
	PlayerMove GetState() { return SMove; }
	void SetPosition(XMFLOAT3 pos) { Position = pos; }
	Sprite* GetSprite() { return iconSprite; }
	CharaTag GetCharaTag() { return ctag; }
protected:
	CharaTag ctag;
	Sprite* iconSprite;
	std::unique_ptr<f_Object3d>m_fbxObject;
	f_Model* m_fbxModel;
protected:
	XMFLOAT3 Position = {0,0,5};
	XMFLOAT3 Scale = { 1,1,1 };
	XMFLOAT3 Rot;
	//��]�p�A���O��
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	PlayerMove SMove;

	int HP;
	int MaxHP;

	int coolTime;
private:
	bool CoolEnd;
	bool isDump;
	bool isStart;
};
