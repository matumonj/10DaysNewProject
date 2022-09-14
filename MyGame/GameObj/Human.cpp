#include "Human.h"
#include"PlaceObj.h"
#include"Sprite.h"
#include"imgui.h"
#include"Collision.h"
#include <Base/Obj/3d/ModelManager.h>

void Human::Initialize() {
	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(ModelManager::GetIns()->GetFBXModel(ModelManager::Human));
	m_fbxObject->PlayAnimation();
	ctag = TPLAYER;
	Range = 25;
	Damage = 10;
	AtkCool = 320.0f;
}

void Human::Update() {
	//PlaceObj::GetInstance()->PlaceChara(iconSprite, this);
	m_fbxObject->SetPosition(Position);
	m_fbxObject->SetScale({ 0.01f,0.01f,0.01f });
	
	
	if (f_time >= m_fbxObject->GetEndTime()) {
		f_time = m_fbxObject->GetEndTime();
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



void Human::Attack(Sushi* sushis)
{
	AttackJudg(sushis);
}



void Human::Attack2(Sushi* sushis)
{
	AttackJudg2(sushis);
}


void Human::Attack3(Sushi* sushis)
{
	AttackJudg3(sushis);
}