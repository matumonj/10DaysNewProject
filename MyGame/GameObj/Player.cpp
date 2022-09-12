#include "Player.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
#include"Destroy.h"



Player::~Player() {
}

void Player::AttackJudg(Sushi* sushis)
{
	if (Collision::GetLength(sushis->GetPos(), Position) < 2.0f) {
		if (CoolTime == 0) {
			AtkFlag = true;
		}
	}


	if (AtkFlag) {
		sushis->RecvDamage(Damage);
		Cool = true;
	}

	if (Cool) {
		CoolTime++;
		if (CoolTime >= AtkCool) {
			Cool = false;
		}
	} else {
		CoolTime = 0;
	}
}