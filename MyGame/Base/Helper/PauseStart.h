#pragma once
#include "Sprite.h"
#include <vector>
#include <memory>


class PauseStart {
public:
	PauseStart();
	~PauseStart();


	void Init();
	void Upda();
	void Draw();


	const bool& GetPause() { return pause; }
private:

	Sprite* num[4] = {};
	std::unique_ptr<Sprite> Go;
	std::vector<int> First;
	bool pause = false;

	float ETime[4] = {};
	float EaseX[4] = { 780, 780, 780, 780 }; //640

	int CoolTime[4] ={ };
	int fase = 0;
};
