#pragma once
#include"Sushi.h"
#include"ScoreMgr.h"

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
		EATEN,
		DEAD
	};
	XMVECTOR move;

	XMMATRIX matRot;
	float RotTime[5];
	SushiMoves SMove;

	XMFLOAT3 position= GatePos, rot,scale;
	bool isDump;
	//ÉSÉ~î†
	const XMFLOAT3 GarbagepPos = { -2,-40,5 };
	//ÉQÅ[Ég
	const XMFLOAT3 GatePos = { 0,-40,-10 };
	const XMFLOAT3 GatePos_Right = { 30, -40, 15 };

public:
	void Wave1or2move(Sushi*sushi);
	void Wave3move(Sushi* sushi);
	void Wave4move(Sushi* sushi);

	void Wave1or2Rot();
	void Wave3Rot();
	void Wave4Rot();
};

