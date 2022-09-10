#pragma once
#include"BaseScene.h"
#include"Sprite.h"
#include <sstream>
#include"sushi.h"


class TitleScene :public BaseScene {
public:
	TitleScene(SceneManager* sceneManager);
private:
	std::unique_ptr<Sprite> BackGround{};

	std::vector<Sushi*> sushis;


public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
};