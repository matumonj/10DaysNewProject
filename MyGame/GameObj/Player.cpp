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
	if (this == nullptr)return;
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
