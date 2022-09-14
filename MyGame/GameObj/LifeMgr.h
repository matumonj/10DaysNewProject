#pragma once
#include "Sprite.h"
#include <vector>
#include <memory>

class LifeMgr final {
private:
	LifeMgr() = default;
	~LifeMgr() = default;
	LifeMgr(const LifeMgr& r) = default;
	LifeMgr& operator= (const LifeMgr& r) = default;

public:

private:
	int life = 3;
	std::unique_ptr<Sprite> LifeRice[3];
public:
	static LifeMgr* GetIns();		//Žæ“¾—p
	void Init();
	void Upda();
	void Draw();

	const int& GetLife() { return life; }
	void SumLife(const int& life) { this->life -= life; }

	void ResetLife() { this->life = 0; }

};