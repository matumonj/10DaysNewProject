#pragma once
#include"Object3d.h"
#include"Model.h"
#include<memory>
class Nail
{
public:
	~Nail();
	static Nail* GetInstance();
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
private:
	std::vector<std::unique_ptr<Object3d>>Nails;
	Model* Nailmodel;
	float MinY= -30 ;
	enum Fase {
		FASE_ONE,
		FASE_TWO,
		FASE_THREE,
		NON
	};

	struct NailParam {
		XMFLOAT3 NailPosition;
		std::vector<int>ZN;
		std::vector<int>XN;
		int WaitCount;
		bool EndAction;
		Fase fase;
	};
	NailParam HAttack;
	NailParam CAttack;
public:
	enum HalfAttackArea {
		RIGHT,
		LEFT
	};
	void HalfAttack(HalfAttackArea area);

	void CircleAttack(int area1,int area2);
	void NailAmountSet(int amount);
	
	void ModelSet();
	void Update();
	void Draw();
	bool GetEndAction_Half() { return HAttack.EndAction; }
	void SetEndAction_Half(bool f) { HAttack.EndAction = f; }
	bool GetEndAction_HalfFase() { if (HAttack.fase == NON) { return true; } else { return false; } }
	bool GetEndAction_Circle() { return CAttack.EndAction; }
};

