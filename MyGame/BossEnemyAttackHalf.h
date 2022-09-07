#pragma once
#include "BossEnemyState.h"
#include"Enemy.h"
class BossEnemyAttackHalf :
    public BossEnemyState
{

public:
	void Initialize(Enemy* enemy)override;

	void Update(Enemy* enemy)override;
private:
	bool judg = true;
};

