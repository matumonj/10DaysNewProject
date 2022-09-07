#include "BossEnemyAttackCircle.h"
#include"BossEnemyFollow.h"
#include"CircleAttack.h"
#include"mHelper.h"
void BossEnemyAttackCircle::Initialize(Enemy* enmey)
{

}

void BossEnemyAttackCircle::Update(Enemy* enemy)
{
	//enemy->SetAttackTime(true);
	CircleAttack::GetInstance()->ActionJudg();
	if (Percent::GetParcent(enemy->GetMaxHP(), enemy->GetHP()) <= 80.0f) {
		enemy->SetAttack_Circle_End(true);
	}
	if (CircleAttack::GetInstance()->GetFaseEnd() == CircleAttack::FASEFOUR) {
		enemy->ChangeState_Boss(new BossEnemyFollow());
	}
}