#pragma once
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"BaseScene.h"
#include <sstream>
#include "mhelper.h"

class ResultScene :public BaseScene {
public:
	ResultScene(SceneManager* sceneManager);
private:
	void LoadRanking();
	void PushBackRank();
	void ResultInit();


	std::stringstream csvRanking;

	std::vector<float> Rank;
	Sprite* num[4][5][10];
	std::vector<int> First;
	std::vector<int> Second;
	std::vector<int> Third;
	std::vector<int> Now;


	float ETime[4] = {};
	float EaseX[4] = { 640,640,640,640 }; //640
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SpriteDraw();
	void Finalize()override;


};