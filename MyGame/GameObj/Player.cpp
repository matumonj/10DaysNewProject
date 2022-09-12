#include "Player.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
#include"Destroy.h"



Player::~Player() {
}

void Player::AttackJudg(Sushi* sushis)
{
	if (Collision::GetLength(sushis->GetPos(), Position) < 20.0f) {
		if (CoolTime == 0) {
			AtkFlag = true;
		}
	}


	if (AtkFlag) {
		sushis->RecvDamage(Damage);
		Cool = true;
		AtkFlag = false;
	}

	if (Cool) {
		CoolTime++;
		if (CoolTime >= AtkCool) {
			Cool = false;
		}
	} 
	else {
		CoolTime = 0;
	}

	EatAction(sushis);
}

void Player::EatAction(Sushi* sushis)
{
	float Speed = 0.1f;
	 float angleX = ( Position.x- sushis->GetPos().x);
	float angleZ = ( Position.z- sushis->GetPos().z);

	//敵とプレイヤーの距離求め
	float dis = sqrtf((Position.x - sushis->GetPos().x) * (Position.x - sushis->GetPos().x)
		+ (Position.z - sushis->GetPos().z) * (Position.z - sushis->GetPos().z));

	//座標のセット
	XMFLOAT3 sushipos= { Position.x + (angleX / dis) * Speed,Position.y,Position.z + (angleZ / dis) * Speed };

	sushis->SetPos(sushipos);
}