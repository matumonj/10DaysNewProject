#include "Bench.h"
#include"CameraControl.h"
#include"Human.h"
#include"PlaceObj.h"
#include"Cat.h"
#include"Input.h"
#include"Bird.h"
#include"mHelper.h"
#include "ImageManager.h"
#include <Base/Obj/3d/ModelManager.h>

Bench::Bench() {
}

Bench::~Bench() {
}

void Bench::Initialize() {
	BenchObj = std::make_unique<Object3d>();
	BenchObj->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Bench));
	BenchObj->Initialize(CameraControl::GetInstance()->GetCamera());

	SiTGauge = Texture::Create(ImageManager::Player, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	SiTGauge->CreateTexture();
	SiTGauge->SetAnchorPoint({ 0,0.5f });

	LeaveF = false;
	SitChara = false;
	Palpha = 1.0f;
}

void Bench::Update(Sushi* sushis) {
	BenchObj->SetScale(Scale);
	BenchObj->SetPosition(Position);
	BenchObj->SetRotation(Rot);
	BenchObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	if (player != nullptr) {
		if (Palpha > 0.5f) {
			player->Attack(sushis);
		}
	}
}

void Bench::Update2(Sushi* sushis) {
	BenchObj->SetScale(Scale);
	BenchObj->SetPosition(Position);
	BenchObj->SetRotation(Rot);
	BenchObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	if (player != nullptr) {
		if (Palpha > 0.5f) {
			player->Attack2(sushis);
		}
	}
}

void Bench::Update3(Sushi* sushis) {
	BenchObj->SetScale(Scale);
	BenchObj->SetPosition(Position);
	BenchObj->SetRotation(Rot);
	BenchObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	if (player != nullptr) {
		if (Palpha > 0.5f) {
			player->Attack3(sushis);
		}
	}
}

void Bench::UpdateS()
{
	SetChara();
	if (player != nullptr) {
		player->Update();

		player->SetPosition(Position);
	}

}

void Bench::SitGaugeUp()
{
	if (SitChara) {
		EsitTime += 1.0f / 600.0f;
		if (EsitTime >= 1.0f) {
			LeaveF = true;
			SitChara = false;
		}
	} else {
		EsitTime = 0.0f;
	}
	SiTGauge->SetBillboard(true);
	SiTGauge->SetScale({ Easing::EaseOut(EsitTime, 50.0f / 20.0f, 0.0f),1,1 });

	SiTGauge->SetPosition({ Position.x,Position.y + 8,Position.z });
	SiTGauge->Update(CameraControl::GetInstance()->GetCamera());

	if (SitChara) {
		Palpha += 0.02f;
	}
	else {
		Palpha -= 0.02f;
	}
	if (player != nullptr) {
		player->SetColor({ 1,1,1,Palpha });
	
		player->SetRot({ 0,Rot.y,0 });
	}
	BenchObj->SetRotation(Rot);
	Palpha = min(Palpha, 1.0f);
	Palpha = max(Palpha, 0.0f);
}
void Bench::Draw() {

	
	BenchObj->PreDraw();
	BenchObj->Draw();
	BenchObj->PostDraw();

	SiTGauge->PreDraw();
	if (SitChara) {
		SiTGauge->Draw();
	}
	SiTGauge->PostDraw();
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
	if (CharaCreate_B) {
		player = new Bird();
		player->Initialize();
		CharaCreate_B = false;
	}
	if (LeaveF) {
		if (Palpha <= 0.0f) {
			delete player;
			player = nullptr;
		}
	}
}