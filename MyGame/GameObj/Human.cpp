#include "Human.h"
#include"PlaceObj.h"
#include"Sprite.h"
#include"imgui.h"
#include"Collision.h"
void Human::Initialize() {
	Sprite::LoadTexture(20, L"Resources/2d/icon/human.png");
	
	iconSprite = Sprite::Create(20, { 700,200 });
	iconSprite->SetSize({ 100,100 });
	iconSprite->setcolor({ 1,1,1,1 });
	iconSprite->SetAnchorPoint({ 0.5f,0.5f });
	
	m_fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("Human");

	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(m_fbxModel);
	m_fbxObject->PlayAnimation();

	ctag = TPLAYER;
//	FbxAnimationControl();

	Damage = 10;
	AtkCool = 120.0f;
}

void Human::Update() {
	//PlaceObj::GetInstance()->PlaceChara(iconSprite, this);
	m_fbxObject->SetPosition(Position);
	m_fbxObject->SetScale({ 0.01f,0.01f,0.01f });
	m_fbxObject->Updata(true);

	//PlaceObj::GetInstance()->SetIconSpritePos(iconSprite);
}

void Human::Draw() {
	//m_fbxObject->Pre
	m_fbxObject->Draw();

}

void Human::IconDraw() {
	Sprite::PreDraw();
	iconSprite->Draw();
	Sprite::PostDraw();

	ImGui::Begin("po");
	ImGui::Text("x %f", iconSprite->GetPosition().x);
	ImGui::Text("y %f", iconSprite->GetPosition().y);
	ImGui::End();
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

void Human::Attack(Sushi* sushis)
{
	AttackJudg(sushis);
}