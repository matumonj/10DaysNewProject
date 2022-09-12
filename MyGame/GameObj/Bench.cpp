#include "Bench.h"
#include"CameraControl.h"
#include"Human.h"
#include"PlaceObj.h"
#include"Cat.h"
#include"Input.h"
#include"mHelper.h"
Bench::Bench() {
}

Bench::~Bench() {
}

void Bench::Initialize() {
	BenchObj = std::make_unique<Object3d>();
	BenchModel = Model::CreateFromOBJ("Bench");
	BenchObj->SetModel(BenchModel);
	BenchObj->Initialize(CameraControl::GetInstance()->GetCamera());

	Texture::LoadTexture(20, L"Resources/2d/SushiHP/HP.png");
	SiTGauge = Texture::Create(1, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
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

	SetChara();
	if (player != nullptr) {
		player->Update();
		if (Palpha > 0.0f) {
			player->Attack(sushis);
		}
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

	SiTGauge->SetPosition({ Position.x,Position.y + 3,Position.z });
	SiTGauge->Update(CameraControl::GetInstance()->GetCamera());

	if (SitChara) {
		Palpha += 0.02f;
	}
	else {
		Palpha -= 0.02f;
	}
	if (player != nullptr) {
		player->SetColor({ 1,1,1,Palpha });
	}
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
	if (LeaveF) {
		if (Palpha <= 0.0f) {
			delete player;
			player = nullptr;
		}
	}
}