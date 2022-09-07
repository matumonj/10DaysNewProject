#pragma once
#include "BossEnemyState.h"
class BossEnemyAttackKnock :
    public BossEnemyState
{

public:
	void Initialize(Enemy* enemy)override;

	void Update(Enemy* enemy)override;
};

