#pragma once
#include"Object3d.h"
#include"Model.h"
#include<memory>
class Sushi
{
protected:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
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
	//��]�^��
	void Moves();
	//��������
	void Rebirth(int cooltime);

	void RotState();
public:
	enum SushiMove {
		GATE,//����
		LANE,//���[�����
		DUMP,//�p��,
		CREATE
	};
protected:
	std::unique_ptr<Object3d>SushiObj;
	Model* SushiModel;

	XMFLOAT3 Position=GatePos;
	XMFLOAT3 Scale={2,2,2};
	XMFLOAT3 Rot;
	//��]�p�A���O��
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	SushiMove SMove;

	int HP;
	int MaxHP;

	int coolTime;
private:
	//�S�~��
	const XMFLOAT3 GarbagepPos = {20,0,-10};
	//�Q�[�g
	const XMFLOAT3 GatePos={ 0,0,-30 };
	bool isDump;
	bool isStart;
};

