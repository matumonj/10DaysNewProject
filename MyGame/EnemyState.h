#pragma once
class Player;
class Enemy;
class EnemyState
{
public:
	~EnemyState();

	virtual void Initialize(Enemy*enmey)=0;

	virtual void Update(Enemy*enemy)=0;


};

