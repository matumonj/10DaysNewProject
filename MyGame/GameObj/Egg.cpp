#include "Egg.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
#include"SushiMove.h"
#include <Base/Obj/3d/ModelManager.h>
void Egg::Initialize()
{
	TexSet();

	SushiObj = std::make_unique<Object3d>();
	SushiModel = ModelManager::GetIns()->GetModel(ModelManager::Egg);
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());
	SushiObj->SetPosition(Position);

	MaxHP = 50;
	HP = MaxHP;
}

void Egg::Update()
{
	if (SushiObj != nullptr) {
		TexUp();
		bool death =  isDead;
		bool eaten = isEaten;
		if (HP <= 0 && !death) {
			Audio::GetInstance()->PlayWave("Resources/Audio/bgm_wav/Eaten.wav", 0.5f);
			ScoreMgr::GetIns()->AddScore(100);
			isDead = true;
		}
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

void Egg::TitleUpda() {
	SushiObj->SetScale(Scale);
	XMFLOAT3 pos = SushiObj->GetPosition();
	if (pos.x <= -10) {
		pos.x = 50;
	}
	pos = { pos.x - 0.1f,-20,-3};
	SushiObj->SetPosition(pos);
	SushiObj->SetRotation(Rot);
	SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

}

void Egg::Draw()
{
	//TexDraw();
	if (SushiObj != nullptr) {
		Object3d::PreDraw();
		SushiObj->Draw();
		Object3d::PostDraw();
	}

	TexDraw();
}
