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
	std::unique_ptr<Sprite> Expadian{};
	std::vector<Sushi*> sushis;

	std::unique_ptr<Sprite> Effect;
	bool Change = false;
	bool Change2 = false;
	bool ExpadianV = false;
	float alpha = 0.0f;
	float frame = 0.0f;
	void Feed();
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
};