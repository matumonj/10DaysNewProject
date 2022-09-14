#include"PlaceObj.h"
#include"CameraControl.h"
#include"Input.h"
#include"Human.h"
#include"Cat.h"
#include "ImageManager.h"

PlaceObj* PlaceObj::GetInstance() {
	static PlaceObj ins;
	return &ins;
}
void PlaceObj::Init() {
	CharaSprite[ONE_GIRL] = Sprite::Create(ImageManager::IconGirl, { 1150,200 });
	CharaSprite[ONE_GIRL]->SetSize({ 100,100 });
	CharaSprite[TWO_CAT] = Sprite::Create(ImageManager::IconCat, { 1150,400 });
	CharaSprite[TWO_CAT]->SetSize({ 100,100 });
	CharaSprite[THREE_BIRD] = Sprite::Create(ImageManager::IconInu, { 1150,600 });
	CharaSprite[THREE_BIRD]->SetSize({ 100,100 });
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		CharaSprite[i]->setcolor({ 1,1,1,1 });
		CharaSprite[i]->SetAnchorPoint({ 0.5f,0.5f });
	}
	StatusSprite[ONE_GIRL] = Sprite::Create(ImageManager::StatusHuman, { 1200,160 });
	StatusSprite[TWO_CAT] = Sprite::Create(ImageManager::StatusCat, { 1200,400 });
	StatusSprite[THREE_BIRD] = Sprite::Create(ImageManager::StatusBird, { 1200,640 });
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		StatusSprite[i]->SetSize({ 100,100 });
		StatusSprite[i]->setcolor({ 1,1,1,1 });
		StatusSprite[i]->SetAnchorPoint({ 0.5f,0.5f });
	}

	Sprite* CharaBack_ = Sprite::Create(ImageManager::IconBack, { 1100,0 });
	CharaBack.reset(CharaBack_);
	std::unique_ptr<Bench> newBench;
	for (int i = 0; i < MAXBENCH; i++) {
		Bench* newBench_ = new Bench();
		newBench_->SetPosition(BenchPos[i]);
		newBench.reset(newBench_);
		Benchs.push_back(std::move(newBench));
	}
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Initialize();
	}

	benchState[LEFT_BOTTOM].Position_2d = { 180,495 };
	benchState[LEFT_BOTTOM].Position_3d = {BenchPos[LEFT_BOTTOM]};
	benchState[LEFT_BOTTOM].SitChara = NON_CHARA;
	Benchs[LEFT_BOTTOM]->SetRot({180,180,0});

	benchState[LEFT_CENTER].Position_2d = { 127,275 };
	benchState[LEFT_CENTER].Position_3d = { BenchPos[LEFT_CENTER]};
	benchState[LEFT_CENTER].SitChara = NON_CHARA;
	Benchs[LEFT_CENTER]->SetRot({ 180,-90,0 });

	benchState[CENTER_UP].Position_2d = { 535,110 };
	benchState[CENTER_UP].Position_3d = { BenchPos[CENTER_UP]};
	benchState[CENTER_UP].SitChara = NON_CHARA;
	Benchs[CENTER_UP]->SetRot({ 0,90,0 });

	benchState[CENTER_BOTTOM].Position_2d = { 490,570 };
	benchState[CENTER_BOTTOM].Position_3d = { BenchPos[CENTER_BOTTOM]};
	benchState[CENTER_BOTTOM].SitChara = NON_CHARA;
	Benchs[CENTER_BOTTOM]->SetRot({ 180,90,0 });

	benchState[LEFT_UP].Position_2d = { 315,145 };
	benchState[LEFT_UP].Position_3d = {BenchPos[LEFT_UP]};
	benchState[LEFT_UP].SitChara = NON_CHARA;
	Benchs[LEFT_UP]->SetRot({ 180,0,0 });

	benchState[RIGHT_BOTTOM].Position_2d = { 710,510 };
	benchState[RIGHT_BOTTOM].Position_3d = { BenchPos[RIGHT_BOTTOM]};
	benchState[RIGHT_BOTTOM].SitChara = NON_CHARA;
	Benchs[RIGHT_BOTTOM]->SetRot({ 0,180,0 });

	benchState[RIGHT_CENTER].Position_2d = { 875,280};
	benchState[RIGHT_CENTER].Position_3d = { BenchPos[RIGHT_CENTER]};
	benchState[RIGHT_CENTER].SitChara = NON_CHARA;
	Benchs[RIGHT_CENTER]->SetRot({ 180,180,0 });

	benchState[RIGHT_UP].Position_2d = { 680,155};
	benchState[RIGHT_UP].Position_3d = { BenchPos[RIGHT_UP]};
	benchState[RIGHT_UP].SitChara = NON_CHARA;
	Benchs[RIGHT_UP]->SetRot({ 180,0,0 });

	
	placeAudio = std::make_unique<Audio>();
	placeAudio->Initialize();

}

void PlaceObj::Update(std::vector<Sushi*> sushis) {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update(sushis);
	}
}

void PlaceObj::Update2(std::vector<Sushi*>  sushis) {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update2(sushis);
	}
}

void PlaceObj::Update3(std::vector<Sushi*>  sushis) {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update3(sushis);
	}
}

void PlaceObj::UpdateS() {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->UpdateS();
	}
}

void PlaceObj::SetIconSpritePos() {
	float x = (float)Input::GetInstance()->GetMousePoint().x;
	float y = (float)Input::GetInstance()->GetMousePoint().y;
	if (Input::GetInstance()->PushMouseLeft()) {
		for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
			if (Collision::GetLength2({ x,y }, CharaSprite[i]->GetPosition()) < 50) {
				if (ClickChara != NON_CHARA) { break; }
				ClickChara = i;
				Clickf[i] = true;
			}
		}
	}
	if (!Input::GetInstance()->PushMouseLeft()) {
		ClickChara = NON_CHARA;
	}
	PlaceChara(ONE_GIRL);
	PlaceChara(TWO_CAT);
	PlaceChara(THREE_BIRD);
	CreateObj(ONE_GIRL);
	CreateObj(TWO_CAT);
	CreateObj(THREE_BIRD);

	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->SitGaugeUp();
	}
}


void PlaceObj::CreateObj(const int& charanum) {
	float x = (float)Input::GetInstance()->GetMousePoint().x;
	float y = (float)Input::GetInstance()->GetMousePoint().y;
	if (Clickf[charanum]) {
		CharaSprite[charanum]->SetPosition({ x,y });
		if (!Input::GetInstance()->PushMouseLeft()) {
			Clickf[charanum] = false;
		}
	}

}

void PlaceObj::PlaceChara(const int& charanum) {
	for (int i = 0; i < MAXBENCH; i++) {
		if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), benchState[i].Position_2d) < 50) {
			if (!Clickf[charanum]) {
				
				if (benchState[i].SitChara != NON_CHARA) { return; }
				if(Benchs[i]->GetRotation().x == 0) {
					Audio::GetInstance()->PlayWave("Resources/Audio/bgm_wav/Cancel.wav", 0.5f);
					SpriteStartPos(charanum);
					break; }
				if (charanum == ONE_GIRL) {
					Audio::GetInstance()->PlayWave("Resources/Audio/bgm_wav/boy.wav", 0.5f);
					Benchs[i]->SetCaharaCreate_P(true);
					benchState[i].SitChara = ONE_GIRL;
				}
				if (charanum == TWO_CAT) {
					Audio::GetInstance()->PlayWave("Resources/Audio/bgm_wav/cat.wav",0.5f);
					Benchs[i]->SetCaharaCreate_C(true);
					benchState[i].SitChara = TWO_CAT;
				}
				if (charanum == THREE_BIRD) {
					Audio::GetInstance()->PlayWave("Resources/Audio/bgm_wav/bird.wav", 0.5f);
					Benchs[i]->SetCaharaCreate_B(true);
					benchState[i].SitChara = THREE_BIRD;
				}
				SpriteStartPos(charanum);
			}
		}
		if (Benchs[i]->GetLeaveF()) {
			benchState[i].SitChara = NON_CHARA;
			Benchs[i]->SetLeaveF(false);
		}
		if (benchState[i].SitChara != NON_CHARA) {
			Benchs[i]->SetCharaSitF(true);
		}
	}

	for (int i = 0; i < MAXBENCH; i++) {
		if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), benchState[i].Position_2d) < 50) {
			break;
		}
		if (i == (MAXBENCH - 1)) {
			if (!Clickf[charanum]) {
				SpriteStartPos(charanum);
			}
		}

	}
}


void PlaceObj::Draw() {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Draw();
	}
	Sprite::PreDraw();
	CharaBack->Draw();
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		StatusSprite[i]->Draw();
	}
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		CharaSprite[i]->Draw();
	}
	Sprite::PostDraw();
}
void PlaceObj::Finalize() {
	for (int i = 0; i < MAX_CHARA;i++) {
		delete CharaSprite[ i];
		delete StatusSprite[i];
	}
	players.clear();
	Benchs.clear();


}
void PlaceObj::SpriteStartPos(const int& charanum) {
	if (charanum == ONE_GIRL) {
		CharaSprite[charanum]->SetPosition({ 1200,60 });
	}
	if (charanum == TWO_CAT) {
		CharaSprite[charanum]->SetPosition({ 1200,300 });
	}
	if (charanum == THREE_BIRD) {
		CharaSprite[charanum]->SetPosition({ 1200,540 });
	}
}

void PlaceObj::LeaveStore() {
	if (benchState[LEFT_BOTTOM].SitChara != NON_CHARA) {
		benchState[LEFT_BOTTOM].LeaveLimit++;
		if (benchState[LEFT_BOTTOM].LeaveLimit >= benchState[LEFT_BOTTOM].LeaveLimit_Max) {

		}
	}
}