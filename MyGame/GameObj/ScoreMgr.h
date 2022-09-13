#pragma once
#include "Sprite.h"
#include <vector>

class ScoreMgr final {
private:
	int score = 100;
	Sprite* num[5][10];
	std::vector<int> First;

public:
	ScoreMgr();

	void Init();
	void Upda();
	void Draw();

	const int& GetScore() { return score; }
	void AddScore(const int& score) { this->score += score;}
	void ResetScore() { this->score = 0; }

};