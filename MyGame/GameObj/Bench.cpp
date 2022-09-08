#include "Bench.h"
#include"CameraControl.h"

Bench::Bench() {
}

Bench::~Bench() {
}

void Bench::Initialize() {
	BenchObj = std::make_unique<Object3d>();
	BenchModel = Model::CreateFromOBJ("Bench");
	BenchObj->SetModel(BenchModel);
	BenchObj->Initialize(CameraControl::GetInstance()->GetCamera());

}

void Bench::Update() {
	BenchObj->SetScale(Scale);
	BenchObj->SetPosition(Position);
	BenchObj->SetRotation(Rot);
	BenchObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

}

void Bench::Draw() {
	BenchObj->PreDraw();
	BenchObj->Draw();
	BenchObj->PostDraw();

}
