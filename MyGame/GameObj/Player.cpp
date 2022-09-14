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

void Player::AttackJudg(std::vector<Sushi*>sushis)
{
	f_time += 0.02f;
	for(int i=0;i<sushis.size();i++){
		if (sushis[i] != nullptr) {
			if (Collision::GetLength(sushis[i]->GetPos(), Position) < Range) {
				if (CoolTime == 0) {
					sushis[i]->RecvDamage(Damage);
					AtkFlag = true;
					Cool = true;
				}
			}
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
		f_time = 0;
		AtkFlag = false;

	}
	
	
}

void Player::AttackJudg2(std::vector<Sushi*>sushis)
{
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
		if (Collision::GetLength(sushis[i]->GetPos(), Position) < Range) {
				if (CoolTime == 0) {
					sushis[i]->RecvDamage(Damage);
					AtkFlag = true;
					Cool = true;
				}
			}
		}
	}


}

void Player::AttackJudg3(std::vector<Sushi*>sushis)
{
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
			if (Collision::GetLength(sushis[i]->GetPos(), Position) < Range) {
				if (CoolTime == 0) {
					sushis[i]->RecvDamage(Damage);
					AtkFlag = true;
					Cool = true;
				}
			}
		}
	}
	

}
