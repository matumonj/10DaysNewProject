#include "Bird.h"
#include"PlaceObj.h"
#include"Sprite.h"
#include"imgui.h"
#include"ModelManager.h"

void Bird::Initialize() {
	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(ModelManager::GetIns()->GetFBXModel(ModelManager::Bird));
	m_fbxObject->PlayAnimation();

	ctag = TPLAYER;
	//	FbxAnimationControl();
	Range = 18;
	Damage = 10;
	AtkCool = 260.0f;
}

void Bird::Update() {
	//PlaceObj::GetInstance()->PlaceChara(iconSprite, this);
	m_fbxObject->SetPosition(Position);
	m_fbxObject->SetScale({ 0.005f,0.005f,0.005f });

	f_time += 0.02f;
	if (f_time >= m_fbxObject->GetEndTime()) {
		f_time = m_fbxObject->GetEndTime();
	}
	
	m_fbxObject->SetFbxTime(f_time);
	m_fbxObject->Updata(true);

}

void Bird::Draw()
{
	m_fbxObject->Draw();
}

void Bird::IconDraw() {

	//ImGui::Begin("po");
	//ImGui::Text("x %f", iconSprite->GetPosition().x);
	//ImGui::Text("y %f", iconSprite->GetPosition().y);
	//ImGui::End();
}

//void Player::FbxAnimationControl() {
//	if (AttackFlag) {
//		f_time = AttackTime;
//		AttackFlag = false;
//		nowattack = true;
//	}
//
//
//	f_time += 0.02f;
//	if (nowattack) {
//		if (f_time >= DeathTime) {
//			f_time = 0;
//			nowattack = false;
//		}
//	} else {
//		if (f_time > AttackTime) {
//			f_time = 0;
//		}
//	}
//
//
//	m_fbxObject->SetFbxTime(f_time);
//}

void Bird::Attack(std::vector<Sushi*> sushis)
{
	AttackJudg(sushis);
}


void Bird::Attack2(std::vector<Sushi*> sushis)
{
	AttackJudg2(sushis);
}

void Bird::Attack3(std::vector<Sushi*> sushis)
{
	AttackJudg3(sushis);
}