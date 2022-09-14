#include "Cat.h"
#include"PlaceObj.h"
#include"Sprite.h"
#include"imgui.h"
#include"ModelManager.h"

void Cat::Initialize() {
	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(ModelManager::GetIns()->GetFBXModel(ModelManager::Cat));
	m_fbxObject->PlayAnimation();

	ctag = TPLAYER;
	//	FbxAnimationControl();

	Range = 20;
	Damage = 20;
	AtkCool = 60.0f;
}

void Cat::Update() {
	//PlaceObj::GetInstance()->PlaceChara(iconSprite, this);
	m_fbxObject->SetPosition(Position);
	m_fbxObject->SetScale({ 0.01f,0.01f,0.01f });

	f_time += 0.02f;
	if (f_time >= m_fbxObject->GetEndTime()) {
		f_time = m_fbxObject->GetEndTime();
	}

	if (Cool) {
		CoolTime++;
		if (CoolTime >= AtkCool) {
			Cool = false;
		}
	} else {
		CoolTime = 0;
	}
	m_fbxObject->SetFbxTime(f_time);
	m_fbxObject->Updata(true);
	m_fbxObject->SetRotation({ Rot.x,Rot.y ,Rot.z });
	//PlaceObj::GetInstance()->SetIconSpritePos(iconSprite);
}

void Cat::Draw()
{
	m_fbxObject->Draw();
}

void Cat::IconDraw() {

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

void Cat::Attack(Sushi* sushis)
{
	AttackJudg(sushis);
}

void Cat::Attack2(Sushi* sushis)
{
	AttackJudg2(sushis);
}

void Cat::Attack3(Sushi* sushis)
{
	AttackJudg3(sushis);
}