#include "Bench.h"
#include"CameraControl.h"
#include"Human.h"
#include"PlaceObj.h"
#include"Cat.h"
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

void Bench::Update(Sushi* sushis) {
	BenchObj->SetScale(Scale);
	BenchObj->SetPosition(Position);
	BenchObj->SetRotation(Rot);
	BenchObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());

	SetChara();
	if (player != nullptr) {
		player->Update();
		player->Attack(sushis);
		player->SetPosition(Position);
	}
}

void Bench::Draw() {
	BenchObj->PreDraw();
	BenchObj->Draw();
	BenchObj->PostDraw();
	if (player != nullptr) {
		player->Draw();
	}
}

void Bench::SetChara()
{
	if (CharaCreate_P) {
		player = new Human();
		player->Initialize();
		CharaCreate_P = false;
	}
	if (CharaCreate_C) {
		player = new Cat();
		player->Initialize();
		CharaCreate_C = false;
	}
	if (CharaCreate_D) {
		player = new Human();
		player->Initialize();
		CharaCreate_D = false;
	}
	if (CharaCreate_B) {
		player = new Human();
		player->Initialize();
		CharaCreate_B = false;
	}
	if (DestroyChara) {
		player = nullptr;
		DestroyChara = false;
	}
}