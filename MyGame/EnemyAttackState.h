#pragma once
#include"EnemyState.h"
#include"Enemy.h"
class EnemyAttackState:public EnemyState
{
public:

	void Initialize(Enemy* enemy)override;

	void Update(Enemy* enemy)override;
};

