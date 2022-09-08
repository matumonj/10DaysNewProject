#include "Tuna.h"
#include"CameraControl.h"
void Tuna::Initialize()
{
	SushiObj = std::make_unique<Object3d>();
	SushiModel = Model::CreateFromOBJ("Tuna");
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());
}

void Tuna::Update()
{
	Moves();
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