#include "Human.h"
#include"PlaceObj.h"
#include"Sprite.h"
#include"imgui.h"
#include"Collision.h"

void Human::Initialize() {
	
	m_fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("Human");

	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(m_fbxModel);
	m_fbxObject->PlayAnimation();

	ctag = TPLAYER;

	Damage = 10;
	AtkCool = 320.0f;
}

void Human::Update() {
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

	//PlaceObj::GetInstance()->SetIconSpritePos(iconSprite);
}

void Human::Draw() {
	//m_fbxObject->Pre
	m_fbxObject->Draw();

}

void Human::IconDraw() {
	Sprite::PreDraw();
	Sprite::PostDraw();

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
//}

void Human::Attack(Sushi* sushis)
{
	AttackJudg(sushis);
}