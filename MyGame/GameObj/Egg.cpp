#include "Egg.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
#include"SushiMove.h"
void Egg::Initialize()
{
	SushiObj = std::make_unique<Object3d>();
	SushiModel = Model::CreateFromOBJ("Egg");
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());

	MaxHP = 50;
	HP = MaxHP;
}

void Egg::Update()
{
		if (SushiObj != nullptr) {
		//Rebirth(3);//クールタイム設定
		SushiObj->SetScale(Scale);
		SushiObj->SetPosition(Position);
		SushiObj->SetRotation(Rot);
		SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	}
}

void Egg::Draw()
{
	SushiObj->PreDraw();
	if (SushiObj != nullptr) {
		SushiObj->Draw();
	}
	SushiObj->PostDraw();

}
