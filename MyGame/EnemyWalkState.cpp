#include "EnemyWalkState.h"
#include"EnemyAttackState.h"
#include"EnemyStayState.h"
#include"EnemyFollowState.h"
#include"Collision.h"
#include"PlayerControl.h"
void EnemyWalkState::Initialize(Enemy* enmey)
{

}
void EnemyWalkState::Update(Enemy* enemy)
{

	float RandMove = rand() % 90 + 20;
	float RandMovement = rand() % 100 + 80;

	//õ“G”ÍˆÍ
	const float DetectionRange = 30.0f;
	//ƒvƒŒƒCƒ„[‚ªõ“G”ÍˆÍ“ü‚Á‚½‚ç
	if (PlayerControl::GetInstance()->GetPlayer() != nullptr) {
		SearchPlayer = Collision::GetLength(enemy->GetPosition(), PlayerControl::GetInstance()->GetPlayer()->GetPosition()) < DetectionRange;
	}
	//ˆÚ“®ƒxƒNƒgƒ‹‚ðyŽ²Žü‚è‚ÌŠp“x‚Å‰ñ“]
	XMVECTOR move = { 0,0,0.1f,0 };
	
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(enemy->GetRotation().y));
	
	move = XMVector3TransformNormal(move, matRot);

	//Œü‚¢‚Ä‚é•ûŒü‚ÉˆÚ“®
	//•à‚¢‚Ä‚¢‚é
	if (enemy->GetonFlag()==true) {
		tempx = enemy->GetPosition().x;
		tempz = enemy->GetPosition().z;
		if (enemy->GetMoveFlag()) {
			enemy->SetPosition({
				enemy->GetPosition().x + move.m128_f32[0],
				enemy->GetPosition().y,
				enemy->GetPosition().z + move.m128_f32[2] }
			);
			movement++;
		}
	
		if (movement > RandMovement) {
			enemy->ChangeState_Mob(new EnemyStayState());
			movement = 0;
		}
	}
	else if (enemy->GetonFlag() == false) {
		if (enemy->GetMoveFlag() != false) {
			enemy->SetPosition({ tempx,enemy->GetPosition().y,tempz });
		}
		else {
			enemy->SetPosition({
							enemy->GetPosition().x ,
							enemy->GetPosition().y,
							enemy->GetPosition().z }
			);

		}
	}
	//UŒ‚
	if (SearchPlayer) {
		//’ÇÕ
		enemy->ChangeState_Mob(new EnemyFollowState());
}
}