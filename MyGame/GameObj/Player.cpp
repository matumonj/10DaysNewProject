#include "Player.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
#include"Destroy.h"



Player::~Player() 
{
	Destroy_unique(m_fbxObject);
	Destroy(iconSprite);
}

void Player::AttackJudg(Sushi* sushis)
{
	f_time += 0.02f;
	if (Collision::GetLength(sushis->GetPos(), Position) < Range) {
		if (CoolTime == 0) {
			AtkFlag = true;
			Cool = true;
		}
	}
	if (Cool) {
		//AtkFlag=false;
		CoolTime++;
		if (CoolTime >= AtkCool) {
			Cool = false;
		}
	} else {
		CoolTime = 0;
	}

	if (AtkFlag) {
		sushis->RecvDamage(Damage);
		f_time = 0;
		AtkFlag = false;

	}
	
}

void Player::AttackJudg2(Sushi* sushis)
{
	if (Collision::GetLength(sushis->GetPos(), Position) < Range) {
		if (CoolTime == 0) {
			AtkFlag2 = true;
		}
	}


	if (AtkFlag) {
		sushis->RecvDamage(Damage);
		Cool = true;
		f_time = 0;
		AtkFlag3 = false;

	}

}

void Player::AttackJudg3(Sushi* sushis)
{
	if (Collision::GetLength(sushis->GetPos(), Position) < Range) {
		if (CoolTime == 0) {
			AtkFlag = true;
		}
	}


	if (AtkFlag) {
		sushis->RecvDamage(Damage);
		Cool = true;
		f_time = 0;
		AtkFlag = false;

	}

}
