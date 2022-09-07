#include "HUDLayOut.h"
#include"HUD.h"
#include"Collision.h"
HUDLayOut* HUDLayOut::GetInstance()
{
	static HUDLayOut instance;

	return &instance;
}
void HUDLayOut::ChangePosition_PlayerHP()
{
	
}

void HUDLayOut::Update()
{
	//マウス座標の取得
	GetCursorPos(&p);
	ScreenToClient(FindWindowA("DirectX", nullptr), &p);
	//LONG->float
	x = p.x;
	y = p.y;

	NowOperation();

	if (LayOutMode) {
		if (operation != ENEMYHP&&operation !=Skill) {//プレイヤー以外のHUDがいじられてないときだけHUD動かせるように
			HUD::GetInstance()->GetPlayerHP()->ChangePosition_PlayerHP({ x,y });
		}
			if (operation!=PLAYERHP&& operation !=Skill) {
				//HUD::GetInstance()->GetEnemyHP()->ChangePosition_PlayerHP({ x,y });
			}
			if (operation != PLAYERHP&& operation != ENEMYHP) {
				HUD::GetInstance()->ChangePosition({ x,y }, center);
			}
			//レイアウトモードをONにした時、瞬時にOFFにならないように
			count++;
		
		if (count>10&&Input::GetInstance()->TriggerKey(DIK_G)) {
			LayOutMode = false;
			count = 0;
		}
	}
	HUD::GetInstance()->SetCenterPosition(center);

}

void HUDLayOut::NowOperation()
{
	////HUD同士が重なるのを防ぐ　かなり汚い方法なのでできたら直したい、、
	if (HUD::GetInstance()->GetPlayerHP()->GetHUDLayOutFlag() == true) {
		operation = PLAYERHP;
	}
	
	if (HUD::GetInstance()->GetSkillButton()->GetHUDLayOutFlag() == true) {
		operation = Skill;
	}
	if (HUD::GetInstance()->GetPlayerHP()->GetHUDLayOutFlag() == false &&
		//HUD::GetInstance()->GetEnemyHP()->GetHUDLayOutFlag() == false&&
		HUD::GetInstance()->GetSkillButton()->GetHUDLayOutFlag() == false) {
		operation = None;
	}
}