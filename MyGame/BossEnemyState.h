#pragma once
class Player;
class Enemy;
class BossEnemyState
{
public:
	virtual ~BossEnemyState();

	virtual void Initialize(Enemy* enmey) = 0;

	virtual void Update(Enemy* enemy) = 0;


};