#include"PlaceObj.h"
#include"CameraControl.h"
#include"Input.h"
#include"Human.h"
#include"Cat.h"
PlaceObj* PlaceObj::GetInstance() {
	static PlaceObj ins;
	return &ins;
}
void PlaceObj::Init() {
	Sprite::LoadTexture(21, L"Resources/2d/CharaIcon/girl.png");
	Sprite::LoadTexture(22, L"Resources/2d/CharaIcon/cat.png");
	Sprite::LoadTexture(23, L"Resources/2d/CharaIcon/inu.png");
	Sprite::LoadTexture(24, L"Resources/2d/CharaIcon/inu.png");
	Sprite::LoadTexture(25, L"Resources/2d/CharaIcon/charaIconB.png");

	CharaSprite[ONE_GIRL] = Sprite::Create(21, { 1150,200 });
	CharaSprite[ONE_GIRL]->SetSize({ 100,100 });
	CharaSprite[TWO_CAT] = Sprite::Create(22, { 1150,400 });
	CharaSprite[TWO_CAT]->SetSize({ 100,100 });
	CharaSprite[THREE_DOG] = Sprite::Create(21, { 1150,500 });
	CharaSprite[THREE_DOG]->SetSize({ 100,100 });
	CharaSprite[FOUR_BIRD] = Sprite::Create(21, { 1150,600 });
	CharaSprite[FOUR_BIRD]->SetSize({ 100,100 });
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		CharaSprite[i]->setcolor({ 1,1,1,1 });
		CharaSprite[i]->SetAnchorPoint({ 0.5f,0.5f });
	}

	Sprite* CharaBack_ = Sprite::Create(25, { 1100,0 });
	CharaBack.reset(CharaBack_);

	benchState[LEFT_BOTTOM].Position_2d = { 200,510 };
	benchState[LEFT_BOTTOM].Position_3d = { -15,-43,0 };
	benchState[LEFT_BOTTOM].SitChara = NON_CHARA;

	benchState[LEFT_CENTER].Position_2d = { 100,300 };
	benchState[LEFT_CENTER].Position_3d = { -15,-43,10 };
	benchState[LEFT_CENTER].SitChara = NON_CHARA;

	benchState[LEFT_UP].Position_2d = { 285,235 };
	benchState[LEFT_UP].Position_3d = { -15,-43,20 };;
	benchState[LEFT_UP].SitChara = NON_CHARA;

	benchState[RIGHT_BOTTOM].Position_2d = { 635,505 };
	benchState[RIGHT_BOTTOM].Position_3d = { 15,-43,0 };
	benchState[RIGHT_BOTTOM].SitChara = NON_CHARA;

	benchState[RIGHT_CENTER].Position_2d = { 802,308};
	benchState[RIGHT_CENTER].Position_3d = { 15,-43,10 };
	benchState[RIGHT_CENTER].SitChara = NON_CHARA;

	benchState[RIGHT_UP].Position_2d = { 645,230};
	benchState[RIGHT_UP].Position_3d = { 15, -43, 20 };
	benchState[RIGHT_UP].SitChara = NON_CHARA;



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


}

void PlaceObj::Update(Sushi* sushis) {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update(sushis);
	}
}

void PlaceObj::UpdateS() {
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->UpdateS();
	}
}

void PlaceObj::SetIconSpritePos() {
	float x = Input::GetInstance()->GetMousePoint().x;
	float y = Input::GetInstance()->GetMousePoint().y;
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
	PlaceChara(THREE_DOG);
	PlaceChara(FOUR_BIRD);
	CreateObj(ONE_GIRL);
	CreateObj(TWO_CAT);
	CreateObj(THREE_DOG);
	CreateObj(FOUR_BIRD);

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
				if (charanum == ONE_GIRL) {
					Benchs[i]->SetCaharaCreate_P(true);
					benchState[i].SitChara = ONE_GIRL;
				}
				if (charanum == TWO_CAT) {
					Benchs[i]->SetCaharaCreate_C(true);
					benchState[i].SitChara = TWO_CAT;
				}
				if (charanum == THREE_DOG) {
					Benchs[i]->SetCaharaCreate_D(true);
					benchState[i].SitChara = THREE_DOG;
				}
				if (charanum == FOUR_BIRD) {
					Benchs[i]->SetCaharaCreate_B(true);
					benchState[i].SitChara = FOUR_BIRD;
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
		CharaSprite[i]->Draw();
	}
	Sprite::PostDraw();
	float x = (float)Input::GetInstance()->GetMousePoint().x;
	float y = (float)Input::GetInstance()->GetMousePoint().y;

	ImGui::Begin("wa ");
	ImGui::Text("x %f", x);
	ImGui::Text("y %f", y);
}
void PlaceObj::SpriteStartPos(const int& charanum) {
	if (charanum == ONE_GIRL) {
		CharaSprite[charanum]->SetPosition({ 1200,100 });
	}
	if (charanum == TWO_CAT) {
		CharaSprite[charanum]->SetPosition({ 1200,250 });
	}
	if (charanum == THREE_DOG) {
		CharaSprite[charanum]->SetPosition({ 1200,400 });
	}
	if (charanum == FOUR_BIRD) {
		CharaSprite[charanum]->SetPosition({ 1200,550 });
	}
}

void PlaceObj::LeaveStore() {
	if (benchState[LEFT_BOTTOM].SitChara != NON_CHARA) {
		benchState[LEFT_BOTTOM].LeaveLimit++;
		if (benchState[LEFT_BOTTOM].LeaveLimit >= benchState[LEFT_BOTTOM].LeaveLimit_Max) {

		}
	}
}