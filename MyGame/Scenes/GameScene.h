#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"
#include"Player.h"
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include"Sushi.h"
#include"Bench.h"
#include"SushiMove.h"
#include <sstream>
#include <Base/Camera/CameraControl.h>
#include "Rail.h"

class GameScene :public BaseScene
{
public:
	GameScene(SceneManager* sceneManager);
private:
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
private:
	std::vector<Sushi*> sushis;
	std::vector<Sushi*> sushis2;

	std::vector< SushiMove*>smove;
	std::vector< SushiMove*>smove2;

	std::unique_ptr<Sprite> BackGround{};

	//ベンチキャラ
	std::list<std::unique_ptr<Rail>> Rails;
	XMFLOAT3 RailPos[12]
		= {
		{0,  -41,-3},{20,-41,13 - 3},{-20,-41,13 - 3},{29,-41,10},
		{-10,-41,15},{ 10, -41, 15},{ 10, -41,7 - 3},{-13,-41,7-3},
	};
	XMFLOAT3 RailRot[12]
		= {
		 {0,-180,0},{0,-180,0},{0,  0,0}, {0,90,0},
		 {0,  90,0},{0,  90,0},{0,-90,0}, {0,-90,0},
	};
	XMFLOAT3 RailSca[12]
		= {
		 {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},
		 {1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1},{1,1,1}
	};

	Player* player;
	Sprite* Gamesprite;
	std::vector<int> sushinum;
	std::vector<bool>activs;
	std::vector<int> sushinum2;

	Sprite* WaveSprite[4];
	float ETime[4];
	bool t, y;
	//スコア関連
	float score = 10;
	std::stringstream csvRanking;
	std::vector<float> Rank;
	void LoadRanking();
	void PushBackRank();
	void ScoreSave(float Score);

	int RandPlaceCount=200;
	int placeC;
	int RandPlaceCount2 = 200;
	int placeC2;
	enum Fase {
		WAVE1=0,
		WAVE2,
		WAVE3,
		WAVE4,
		CLEAR
	};
	Fase fase;
	int RetrandCount();
	void WaveCont();
	int SushiDeathCount;

	void Wave1or2();
	void Wave3();
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SpriteDraw();
	void Finalize()override;


};

