#include "BossEnemyDeath.h"
#include"BossEnemyFollow.h"
void BossEnemyDeath::Initialize(Enemy* enmey)
{

}

void BossEnemyDeath::Update(Enemy* enemy)
{
	enemy->Death();
	//enemy->ChangeState_Boss(new BossEnemyFollow());
}