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

class TitleScene :public BaseScene
{
public:
	TitleScene(SceneManager* sceneManager);
private:
	std::vector<Sushi*> sushis;
	std::list<std::unique_ptr<Bench>> Benchs;
	Sprite* titlesprite;
	std::vector<int> sushinum;
	std::vector<bool>activs;
	Sprite* WaveSprite[4];
	float ETime[4];
	bool t, y;
	//DirectXCommon* dxcomn;
	int RandPlaceCount=200;
	int placeC;
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
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SpriteDraw();
	void Finalize()override;


};

