#pragma once
#include "Sprite.h"
#include <vector>
#include <memory>

class ScoreMgr final {
private:
	ScoreMgr() = default;
	~ScoreMgr() = default;
	ScoreMgr(const ScoreMgr & r) = default;
	ScoreMgr& operator= (const ScoreMgr & r) = default;

public:

private:
	int score = 100;
	Sprite* num[5][10]={};
	std::unique_ptr<Sprite> Doll;
	std::vector<int> First;
public:
	static ScoreMgr* GetIns();		//Žæ“¾—p
	void Init();
	void Upda();
	void Draw();

	const int& GetScore() { return score; }
	void AddScore(const int& score) { this->score += score;}
	void ResetScore() { this->score = 0; }

};