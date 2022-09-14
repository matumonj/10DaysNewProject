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
#include "ScoreMgr.h"
#include"PauseStart.h"

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
	std::vector<Sushi*> sushis3;

	std::vector< SushiMove*>smove;
	std::vector< SushiMove*>smove2; 
	std::vector< SushiMove*>smove3;

	std::unique_ptr<Sprite> BackGround{};


	std::unique_ptr<Object3d> DustBox;
	Model* Dust;
	std::unique_ptr<Object3d> Gate;
	std::unique_ptr<Object3d> Gate2;
	Model* GateModel;

	//ベンチキャラ
	std::list<std::unique_ptr<Rail>> Rails;
	const float y = -41;
	XMFLOAT3 RailPos[12]
		= {
		//	下と２レーン		
		{0.5f, y,-3.5f},{29,y,15},
		//左右
		{19.5f,y,9.5f},{19.5f,y,20},{-20,y,13 - 3},{-20,y,20},
		//上下
		{-10,y,27},{ 10, y,27},{ 10,y,7 - 3},{-14,y,7-3},
		{0.5f, y,35.0f}
	};
	XMFLOAT3 RailRot[12]
		= {
		 {0,-180,0}, {0,90,0},
		{0,-180,0},{0,-180,0},{0,0,0},{0, 0,0}, 
		{0,  90,0},{0,  90,0},{0,-90,0}, {0,-90,0},
	};
	XMFLOAT3 RailSca[12]
		= {
		 {1.2f,1,1.25f},{1.2f,1,1},
		{1.2f,1,1},{1.2f,1,1},{1.2f,1,1},{1.2f,1,1},
		 {1.2f,1,1.5f},{1.2f,1,1.5f},{1.2f,1,1},{1.2f,1,1},{1.2f,1,1},{1.2f,1,1}
	};

	Sprite* Gamesprite;
	std::vector<int> sushinum;
	std::vector<bool>activs;
	std::vector<int> sushinum2;
	std::vector<int> sushinum3;
	Sprite* WaveSprite[4];
	float ETime[4];
	//スコア関連
	std::stringstream csvRanking;
	std::vector<float> Rank;
	void LoadRanking();
	void PushBackRank();
	void ScoreSave(float Score);

	int RandPlaceCount=200;
	int placeC;
	int RandPlaceCount2 = 200;
	int RandPlaceCount3 = 300;
	int placeC2;
	int placeC3;
	enum Fase {
		WAVE1=0,
		WAVE2,
		WAVE3,
		WAVE4,
		WAVE5,
		WAVE6,
		CLEAR
	};
	Fase fase;
	int RetrandCount();
	int RetrandCount2();
	int RetrandCount3();
	void WaveCont();
	int SushiDeathCount;
	PauseStart* pauseStart;
	bool first = false;
	bool pause = true;
	void Wave1or2();
	void Wave3();
	void Wave4();
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SpriteDraw();
	void Finalize()override;


};

