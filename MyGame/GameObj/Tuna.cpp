#include "Tuna.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
#include"SushiMove.h"
void Tuna::Initialize()
{
	TexSet();
	SushiObj = std::make_unique<Object3d>();
	SushiModel = Model::CreateFromOBJ("Tuna");
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
		bool death = (HP <= 0);
		//Rebirth(30);
		SushiObj->SetScale(Scale);
		SushiObj->SetPosition(Position);
		SushiObj->SetRotation(Rot);
		SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

	}
	HP = min(HP, MaxHP);
	HP = max(HP, 0);
}

void Tuna::TitleUpda() {
	SushiObj->SetScale(Scale);
	XMFLOAT3 pos = SushiObj->GetPosition();
	if (pos.x <= -25) {
		pos.x = 25;
	}
	pos = { pos.x - 0.1f,-20,0 };
	SushiObj->SetPosition(pos);
	SushiObj->SetRotation(Rot);
	SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

}

void Tuna::Draw()
{
	if (SushiObj != nullptr) {
		TexDraw();
		SushiObj->PreDraw();
		SushiObj->Draw();
		SushiObj->PostDraw();
	}
}
