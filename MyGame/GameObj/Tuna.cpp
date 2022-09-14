#include "Tuna.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
#include"SushiMove.h"
#include "ModelManager.h"
#include "ScoreMgr.h"

void Tuna::Initialize()
{
	TexSet();
	SushiObj = std::make_unique<Object3d>();
	SushiModel = ModelManager::GetIns()->GetModel(ModelManager::Tuna);
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());
	SushiObj->SetPosition(Position);

	MaxHP = 30;
	HP = MaxHP;
}

void Tuna::Update()
{
	//SushiMove::GetInstance()->Wave1or2move(this);
	//Moves();
	if (SushiObj!=nullptr) {
		TexUp();
		bool death = isDead;
		bool eaten = isEaten;
		if (HP==0 && !death) {
			ScoreMgr::GetIns()->AddScore(100);
			isDead = true;
		}
		//Rebirth(30);
		SushiObj->SetScale(Scale);
		SushiObj->SetPosition(Position);
		SushiObj->SetRotation(Rot);
		SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
		if (death) {
			Scale.x -= 0.05f;
			Scale.z -= 0.05f;
		}
	}

	Scale.x = max(Scale.x, 0);
	Scale.x = min(Scale.x, 2);
	Scale.z = max(Scale.z, 0);
	Scale.z = min(Scale.z, 2);
	HP = min(HP, MaxHP);
	HP = max(HP, 0);
}

void Tuna::TitleUpda() {
	SushiObj->SetScale(Scale);
	XMFLOAT3 pos = SushiObj->GetPosition();
	if (pos.x <= -10) {
		pos.x = 50;
	}
	pos = { pos.x - 0.1f,-20,-3 };
	SushiObj->SetPosition(pos);
	SushiObj->SetRotation(Rot);
	SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

}

void Tuna::Draw()
{
	TexDraw();
	if (SushiObj != nullptr) {
		Object3d::PreDraw();
		SushiObj->Draw();
		Object3d::PostDraw();
	}
	//TexDraw();
}
