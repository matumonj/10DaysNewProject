#include "EnemyDeathState.h"
#include"EnemyStayState.h"
void EnemyDeathState::Initialize(Enemy* enmey)
{

}

void EnemyDeathState::Update(Enemy* enemy)
{
	enemy->Death();
}