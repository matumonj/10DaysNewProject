#pragma once
#include "EnemyState.h"
#include"Enemy.h"
class EnemyDeathState :
    public EnemyState
{
public:

	void Initialize(Enemy* enemy);

	void Update(Enemy* enemy);

};

