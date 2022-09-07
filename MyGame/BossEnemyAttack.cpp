#include "BossEnemyAttack.h"
#include"BossEnemyFollow.h"
void BossEnemyAttack::Initialize(Enemy* enmey)
{

}

void BossEnemyAttack::Update(Enemy* enemy)
{
	enemy->SetAttackTime(true);
	enemy->ChangeState_Boss(new BossEnemyFollow());
}