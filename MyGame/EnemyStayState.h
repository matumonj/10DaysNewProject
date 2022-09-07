#pragma once
#include"Enemy.h"
#include"EnemyState.h"
class EnemyStayState :public EnemyState
{
public:

	void Initialize(Enemy* enemy);

	void Update(Enemy* enemy);

private:
	float BeforeRot;
	float rot;
	float tempx, tempz;
	float AfterRot;
	float RotTime = 0;
	int StayCount = 0;
};

