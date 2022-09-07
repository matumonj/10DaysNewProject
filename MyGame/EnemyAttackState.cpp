#include "EnemyAttackState.h"
#include"EnemyStayState.h"
void EnemyAttackState::Initialize(Enemy*enmey)
{

}

void EnemyAttackState::Update(Enemy* enemy)
{
	enemy->SetAttackTime(true);
	enemy->ChangeState_Mob(new EnemyStayState());
}