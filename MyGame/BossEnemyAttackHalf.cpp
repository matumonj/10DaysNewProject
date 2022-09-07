#include "BossEnemyAttackHalf.h"
#include"BossEnemyFollow.h"
#include"HalfAttack.h"
#include"mHelper.h"
void BossEnemyAttackHalf::Initialize(Enemy* enmey)
{

}

void BossEnemyAttackHalf::Update(Enemy* enemy)
{
	//enemy->SetAttackTime(true);
	HalfAttack::GetInstance()->ActionJudg();
	if (Percent::GetParcent(enemy->GetMaxHP(), enemy->GetHP()) <= 80.0f) {
		enemy->SetAttack_Half_End(true);
	}
	if (Percent::GetParcent(enemy->GetMaxHP(), enemy->GetHP()) <= 40.0f) {
		enemy->SetAttack_Half2_End(true);
	}
	if (HalfAttack::GetInstance()->GetFaseEnd()==HalfAttack::FASEFOUR) {
		enemy->ChangeState_Boss(new BossEnemyFollow());
	}
}