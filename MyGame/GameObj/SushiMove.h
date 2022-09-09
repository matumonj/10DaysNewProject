#pragma once
#include"Sushi.h"
class SushiMove
{
private:
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;
public:
	static SushiMove* GetInstance();
private:
	enum SushiMoves {
		GATE,//ì¸èÍ
		LANE,//ÉåÅ[ÉìâÒÇÈ
		DUMP,//îpä¸,
		CREATE,
		DEAD
	};
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	SushiMoves SMove;

	XMFLOAT3 position= GatePos, rot,scale;
	bool isDump;
	//ÉSÉ~î†
	const XMFLOAT3 GarbagepPos = { -5,0,5 };
	//ÉQÅ[Ég
	const XMFLOAT3 GatePos = { 0,0,-10 };
	const XMFLOAT3 GatePos_Right = { -30, 0, 10 };

public:
	void Wave1or2move(Sushi*sushi);
	void Wave3move(Sushi* sushi);

	void Wave1or2Rot();
	void Wave3Rot();
};

