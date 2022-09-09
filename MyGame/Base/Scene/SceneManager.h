#pragma once
#include"BaseScene.h"
#include<thread>

class SceneManager
{
public:
	static SceneManager* GetInstance();
	//更新
	void Update();
	//描画
	void Draw();
	//次のシーンへ移行するためのセッター
	void SetnextScene(BaseScene* nextScene_) { nextScene = nextScene_; }

	void Finalize();
	
	enum NowScene{
		TITLE,
		TUTORIAL,
		PLAY,
		BOSS,
		RESULT,
	};
	NowScene GetScene() { return scene; }
	void SetScene(NowScene scene) { this->scene=scene; }
private:
	
	NowScene scene = TITLE;
	std::thread t;
	BaseScene* Scene;
	BaseScene* nextScene = nullptr;
};

