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

	CharaSprite[ONE_GIRL] = Sprite::Create(21, { 1100,200 });
	CharaSprite[ONE_GIRL]->SetSize({ 100,100 });
	CharaSprite[TWO_CAT] = Sprite::Create(22, { 1100,300 });
	CharaSprite[TWO_CAT]->SetSize({ 100,100 });
	CharaSprite[THREE_DOG] = Sprite::Create(21, { 1100,400 });
	CharaSprite[THREE_DOG]->SetSize({ 100,100 });
	CharaSprite[FOUR_BIRD] = Sprite::Create(21, { 1100,500 });
	CharaSprite[FOUR_BIRD]->SetSize({ 100,100 });
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		CharaSprite[i]->setcolor({ 1,1,1,1 });
		CharaSprite[i]->SetAnchorPoint({ 0.5f,0.5f });
	}

	benchState[LEFT_BOTTOM].Position_2d = { 418,500 };
	benchState[LEFT_BOTTOM].Position_3d = { -15,-43,0 };
	benchState[LEFT_BOTTOM].SitChara = NON_CHARA;

	benchState[LEFT_UP].Position_2d = { 460,260 };
	benchState[LEFT_UP].Position_3d = { -15,-43,20 };;
	benchState[LEFT_UP].SitChara = NON_CHARA;

	benchState[RIGHT_BOTTOM].Position_2d = { 860,505 };
	benchState[RIGHT_BOTTOM].Position_3d = { 15,-43,0 };
	benchState[RIGHT_BOTTOM].SitChara = NON_CHARA;

	benchState[RIGHT_UP].Position_2d = { 822,265 };
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

void PlaceObj::SetIconSpritePos() {
	float x = Input::GetInstance()->GetMousePoint().x;
	float y = Input::GetInstance()->GetMousePoint().y;
	if (Input::GetInstance()->PushMouseLeft()) {
		//if (ClickChara != NON_CHARA) { return; }
		for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
			if (Collision::GetLength2({ x,y }, CharaSprite[i]->GetPosition()) < 50) {
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
	float x = Input::GetInstance()->GetMousePoint().x;
	float y = Input::GetInstance()->GetMousePoint().y;
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
	for (int i = ONE_GIRL; i < MAX_CHARA; i++) {
		CharaSprite[i]->Draw();
	}
	Sprite::PostDraw();

}
void PlaceObj::SpriteStartPos(const int& charanum) {
	if (charanum == ONE_GIRL) {
		CharaSprite[charanum]->SetPosition({ 1100,200 });
	}
	if (charanum == TWO_CAT) {
		CharaSprite[charanum]->SetPosition({ 1100,300 });
	}
	if (charanum == THREE_DOG) {
		CharaSprite[charanum]->SetPosition({ 1100,400 });
	}
	if (charanum == FOUR_BIRD) {
		CharaSprite[charanum]->SetPosition({ 1100,500 });
	}
}

void PlaceObj::LeaveStore() {
	if (benchState[LEFT_BOTTOM].SitChara != NON_CHARA) {
		benchState[LEFT_BOTTOM].LeaveLimit++;
		if (benchState[LEFT_BOTTOM].LeaveLimit >= benchState[LEFT_BOTTOM].LeaveLimit_Max) {

		}
	}
}