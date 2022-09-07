#include "EnemyStayState.h"
#include "EnemyWalkState.h"
#include"EnemyAttackState.h"
#include"EnemyFollowState.h"
#include"mHelper.h"
#include"EnemyDeathState.h"
void EnemyStayState::Initialize(Enemy* enemy)
{

}
void EnemyStayState::Update(Enemy* enemy)
{
	float RandMove = rand() % 90 + 40;
	if (StayCount == 0) {
		//ƒC[ƒWƒ“ƒOŠ|‚¯‚é‘O‚Ì“G‚ÌŒü‚«
		BeforeRot = enemy->GetRotation().y;
		//Š|‚¯‚½Œã‚Ì“G‚ÌŒü‚«
		AfterRot = enemy->GetRotation().y  +RandMove;
	}
	
	StayCount++;
	if (StayCount > 90) {//’âŽ~ŽžŠÔ
		RotTime += 0.01f;
		enemy->SetRotation({
			enemy->GetRotation().x,
			Easing::EaseOut(RotTime,BeforeRot, AfterRot),
			enemy->GetRotation().z
			});
		if (RotTime>0.6) {
			enemy->ChangeState_Mob(new EnemyWalkState());
		}
	}

	if (enemy->GetHP() <= 0.0f) {
		enemy->ChangeState_Mob(new EnemyDeathState());
	}
}
