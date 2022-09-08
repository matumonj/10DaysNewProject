#include "Egg.h"
#include"CameraControl.h"
#include"WinApp.h"
#include"imgui.h"
void Egg::Initialize()
{
	SushiObj = std::make_unique<Object3d>();
	SushiModel = Model::CreateFromOBJ("Tuna");
	SushiObj->SetModel(SushiModel);
	SushiObj->Initialize(CameraControl::GetInstance()->GetCamera());

	MaxHP = 50;
	HP = MaxHP;
}

void Egg::Update()
{
	bool death = (HP <= 0)||(Collision::GetLength(Position,GarbagepPos)<1);
	Moves();//回転
	Rebirth(3);//クールタイム設定
	SushiObj->SetScale(Scale);
	SushiObj->SetPosition(Position);
	SushiObj->SetRotation(Rot);
	SushiObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

	if (death) {
		SMove = DUMP;
	}
}

void Egg::Draw()
{
	SushiObj->PreDraw();
	if (SMove != DUMP) {
		SushiObj->Draw();
	}
	SushiObj->PostDraw();

}
