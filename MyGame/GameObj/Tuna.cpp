#include "Tuna.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
void Tuna::Initialize()
{
	SushiObj = std::make_unique<Object3d>();
	SushiModel = Model::CreateFromOBJ("Tuna");
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());

	MaxHP = 30;
	HP = MaxHP;
}

void Tuna::Update()
{
	bool death = (HP <= 0);
	//Rebirth(30);
	Moves(5);
	SushiObj->SetScale(Scale);
	SushiObj->SetPosition(Position);
	SushiObj->SetRotation(Rot);
	SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

}

void Tuna::Draw()
{
	SushiObj->PreDraw();
	SushiObj->Draw();
	SushiObj->PostDraw();

}