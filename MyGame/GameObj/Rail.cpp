#include "Rail.h"
#include <Base/Camera/CameraControl.h>

Rail::Rail() {
}

Rail::~Rail() {
}

void Rail::Initialize() {
	RailObj = std::make_unique<Object3d>();
	RailModel = Model::CreateFromOBJ("Conveyor");
	RailObj->SetModel(RailModel);
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
