#pragma once
#include"BaseScene.h"
#include"Sprite.h"
#include <sstream>


class TitleScene :public BaseScene {
public:
	TitleScene(SceneManager* sceneManager);
private:
	std::unique_ptr<Sprite> BackGround{};

	//std::list<std::unique_ptr<Sushi*>> sushis;


public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
};