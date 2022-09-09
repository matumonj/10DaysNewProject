#include "Tuna.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
void Tuna::Initialize()
{
	TexSet();
	SushiObj = std::make_unique<Object3d>();
	SushiModel = Model::CreateFromOBJ("Tuna");
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());

	MaxHP = 30;
	HP = MaxHP;
}

void Tuna::Update()
{
	Moves(5);
	if (SushiObj!=nullptr) {
		TexUp();
		bool death = (HP <= 0);
		//Rebirth(30);
		SushiObj->SetScale(Scale);
		SushiObj->SetPosition(Position);
		SushiObj->SetRotation(Rot);
		SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

	}
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
