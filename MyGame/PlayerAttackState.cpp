
#include "PlayerAttackState.h"
#include"Input.h"
#include"EnemyControl.h"
#include"Collision.h"
#include"CustomButton.h"
#include"PlayerControl.h"
#include"SelectSword.h"
#include"AttackCollision.h"
#include"SceneManager.h"
#include"HUD.h"
PlayerAttackState* PlayerAttackState::GetInstance()
{
	static PlayerAttackState instance;

	return &instance;
}

void PlayerAttackState::ComboAction()
{
	if (OldSkill == First) {
		if (Skill == Second) {
			ComboFirst = true;
		}
	}
	if (OldSkill == Second) {
		if (Skill == Third) {
			ComboLast = true;
		}
	}
	
}
void PlayerAttackState::Update()
{
	
	index =  TargetMarker::GetInstance()->GetNearIndex();

//	if (AttackJudgeMent) {
		if (CustomButton::GetInstance()->GetAttackAction()==true ){ /*CoolDownTime == 0*/
			Skill = First;
		} /*else if (Input::GetInstance()->PushButton(Input::GetInstance()->Button_A) && CoolDownTime == 0) {
			Skill = Second;
		} else if (Input::GetInstance()->PushButton(Input::GetInstance()->Button_X) && CoolDownTime == 0) {
			Skill = Third;
		} else if (Input::GetInstance()->PushButton(Input::GetInstance()->Button_Y) && BufCoolDownTime == 0) {
			BuffFlag = true;
		}*/
	//}
	if (BuffFlag) {
		//バフ継続時間
		BuffTime++;
	}

	ComboAction();

	switch (Skill)
	{
	case PlayerAttackState::None:
		break;
	case PlayerAttackState::First:
		if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
			FirstAttack(EnemyControl::GetInstance()->GetTutorialEnemyindex());
		}
		if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
			FirstAttack(EnemyControl::GetInstance()->GetEnemyindex(0));
		}
		if (SceneManager::GetInstance()->GetScene() == SceneManager::BOSS) {
			FirstAttack(EnemyControl::GetInstance()->GetBossEnemyindex());
		}
		break;
	case PlayerAttackState::Second:
		//SecondAttack(EnemyControl::GetInstance()->GetEnemyindex(1)
		//);
		break;
	case PlayerAttackState::Third:
		//ThirdAttack(EnemyControl::GetInstance()->GetEnemyindex(1)
		//);
		break;
	}
	//スキルクールダウン処理
	SkillCoolDown(CoolDownTime);

}

void PlayerAttackState::FirstAttack(std::vector<std::unique_ptr<Enemy>>& enemy)
{
	//2巡目のコンボ打消
	ComboLast = false;
	//
	OldSkill = First;
	
	Damage = SelectSword::GetInstance()->GetSword()->GetDamage()+FIRSTATTACKDAMAGE;
	
	DetailAttack(enemy,120);
}

void PlayerAttackState::SecondAttack(std::vector<std::unique_ptr<Enemy>>& enemy)
{
	OldSkill = Second;
	
	if (ComboFirst) {//コンボ時のダメージ
		Damage = SelectSword::GetInstance()->GetSword()->GetDamage() + SECONDATTACKDAMAGE+COMBOBONUS;
	}else {//通常ダメージ
		Damage = SelectSword::GetInstance()->GetSword()->GetDamage() + SECONDATTACKDAMAGE ;
	}

	DetailAttack(enemy,120);
//}
}

void PlayerAttackState::ThirdAttack(std::vector<std::unique_ptr<Enemy>>& enemy)
{
	//
	OldSkill = Third;
	//1巡目のコンボ打消
	ComboFirst = false;

	if (ComboLast) {//コンボ時のダメージ
		Damage = SelectSword::GetInstance()->GetSword()->GetDamage() + ThirdAttackDamage+ComboBonus;
	} else {//通常のダメージ
		Damage = SelectSword::GetInstance()->GetSword()->GetDamage() + ThirdAttackDamage;
	}
	DetailAttack(enemy,120);
//}
}


void PlayerAttackState::BuffAction()
{
	//普通の攻撃の25%をバフ値に
	const int Magnification = Damage/4;

		if (BuffTime <= BuffTimeMax) {//効果時間は20秒
			if (Skill != None) {
				Damage += Magnification;
			}
		} else if(BuffTime>BuffTimeMax){
			BuffTime = 0;
			BuffFlag = false;
		}
}

void PlayerAttackState::SkillCoolDown(int &cooltime)
{
	cooltime--;
	cooltime= max(cooltime, 0);
	cooltime = min(cooltime, 120);
}

void PlayerAttackState::DetailAttack(std::vector<std::unique_ptr<Enemy>>& enemy,int cooltime)
{
	if (enemy[0] == nullptr)return;
	//クールタイムを設定
	CoolDownTime = SelectSword::GetInstance()->GetSword()->GetCoolTime();
	//バフがかかっていた場合
	if (BuffFlag) {
		BuffAction();
	}
	//敵に対して攻撃
	AttackCollision::GetInstance()->GetCol(Damage);
	//if (/*fbxのモーション終わったら*/) {
	Skill = None;
}
