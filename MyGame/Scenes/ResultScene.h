#pragma once
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"BaseScene.h"
#include <sstream>

class ResultScene :public BaseScene {
public:
	ResultScene(SceneManager* sceneManager);
private:
	void LoadRanking();
	void PushBackRank();

	void ScoreSave(float Score);


	std::stringstream csvRanking;

	std::vector<float> Rank;
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void SpriteDraw();
	void Finalize()override;


};