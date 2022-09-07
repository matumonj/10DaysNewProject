#pragma once
#include"EnemyState.h"
#include"Enemy.h"
class EnemyWalkState :public EnemyState 
{
public:
	void Initialize(Enemy*enemy)override;

	void Update(Enemy*enemy)override;
private:
	float tempx, tempz;
	int movement;
	bool SearchPlayer;
};

