#include "Rail.h"
#include <Base/Camera/CameraControl.h>
#include"imgui.h"
#include <Base/Obj/3d/ModelManager.h>
Rail::Rail() {
}

Rail::~Rail() {
}

void Rail::Initialize() {
	RailObj = std::make_unique<Object3d>();
	RailObj->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Conveyor));
	RailObj->Initialize(CameraControl::GetInstance()->GetCamera());

}

void Rail::Update() {
	RailObj->SetScale(Scale);
	RailObj->SetPosition(Position);
	RailObj->SetRotation(Rot);
	RailObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

}

void Rail::Draw() {
	RailObj->PreDraw();
	RailObj->Draw();
	RailObj->PostDraw();
}
