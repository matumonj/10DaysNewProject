#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"

#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include"Sushi.h"
#include"Bench.h"
<<<<<<< HEAD
#include"SushiMove.h"
=======
#include <sstream>

>>>>>>> 7462e226febaf65a0008333e59e51dc11af6168f
class TitleScene :public BaseScene
{
public:
	TitleScene(SceneManager* sceneManager);
private:
	std::vector<Sushi*> sushis;
	std::vector<Sushi*> sushis2;

	std::vector< SushiMove*>smove;
	std::vector< SushiMove*>smove2;
	std::list<std::unique_ptr<Bench>> Benchs;
	Sprite* titlesprite;
	std::vector<int> sushinum;
	std::vector<bool>activs;
	std::vector<int> sushinum2;
	//std::vector<bool>activs;
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
		WAVE1,
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

