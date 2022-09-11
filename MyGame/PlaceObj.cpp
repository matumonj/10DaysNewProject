#include"PlaceObj.h"
#include"CameraControl.h"
#include"Input.h"
#include"Human.h"
#include"Cat.h"
PlaceObj* PlaceObj::GetInstance()
{
	static PlaceObj ins;
	return &ins;
}
void PlaceObj::Init()
{
	mod = Model::CreateFromOBJ("Tuna");
	obj = new Object3d();
	obj->SetModel(mod);
	obj->Initialize(CameraControl::GetInstance()->GetCamera());

	Sprite::LoadTexture(21, L"Resources/2d/CharaIcon/girl.png");
	Sprite::LoadTexture(22, L"Resources/2d/CharaIcon/cat.png");
	Sprite::LoadTexture(23, L"Resources/2d/CharaIcon/inu.png");
	Sprite::LoadTexture(24, L"Resources/2d/CharaIcon/inu.png");

	CharaSprite[0] = Sprite::Create(21, { 700,200 });
	CharaSprite[0]->SetSize({ 100,100 });
	CharaSprite[1] = Sprite::Create(21, { 700,300 });
	CharaSprite[1]->SetSize({ 100,100 });
	CharaSprite[2] = Sprite::Create(21, { 700,400 });
	CharaSprite[2]->SetSize({ 100,100 });
	CharaSprite[3] = Sprite::Create(21, { 700,500 });
	CharaSprite[3]->SetSize({ 100,100 });
	for (int i = 0; i < 4; i++) {
		CharaSprite[i]->setcolor({ 1,1,1,1 });
		CharaSprite[i]->SetAnchorPoint({ 0.5f,0.5f });
	}

	Bench_LB.Position_2d = { 418,500 };
	Bench_LB.Position_3d = { -15,-43,0 };
	Bench_LB.schara = NON;

	Bench_LU.Position_2d = { 460,260 };
	Bench_LU.Position_3d = { -15,-43,20 };;
	Bench_LU.schara = NON;

	Bench_RB.Position_2d = { 860,505 };
	Bench_RB.Position_3d = { 15,-43,0 };
	Bench_RB.schara = NON;

	Bench_RU.Position_2d = { 822,265 };
	Bench_RU.Position_3d = { 15, -43, 20 };
	Bench_RU.schara = NON;



	std::unique_ptr<Bench> newBench;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			Bench* newBench_ = new Bench();
			newBench_->SetPosition(BenchPos[j][i]);
			newBench.reset(newBench_);
			Benchs.push_back(std::move(newBench));
		}
	}
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Initialize();
	}


}

void PlaceObj::Update()
{
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update();
	}
 }

void PlaceObj::SetIconSpritePos()
{
	float x = Input::GetInstance()->GetMousePoint().x;
	float y = Input::GetInstance()->GetMousePoint().y;
	if (Input::GetInstance()->PushMouseLeft()&&cChara==CNON) {
		if (Collision::GetLength2({ x,y }, CharaSprite[0]->GetPosition()) < 50 == true)
		{
			cChara = CPLAYER;
			Clickf[0] = true;
		}
		if (Collision::GetLength2({ x,y }, CharaSprite[1]->GetPosition()) < 50 == true)
		{
			cChara = CCAT;
			Clickf[1] = true;
		}
		if (Collision::GetLength2({ x,y }, CharaSprite[2]->GetPosition()) < 50 == true)
		{
			cChara = CDOG;
			Clickf[2] = true;
		}
		if (Collision::GetLength2({ x,y }, CharaSprite[3]->GetPosition()) < 50 == true)
		{
			cChara = CBIRD;
			Clickf[3] = true;
		}
	}
	if (!Input::GetInstance()->PushMouseLeft()) {
		cChara = CNON;
	}
	PlaceChara(ONE_GIRL);
	PlaceChara(TWO_CAT);
	PlaceChara(THREE_DOG);
	PlaceChara(FOUR_BIRD);
	CreateObj(ONE_GIRL);
	CreateObj(TWO_CAT);
	CreateObj(THREE_DOG);
	CreateObj(FOUR_BIRD);
}


void PlaceObj::CreateObj(int charanum)
{

	float x = Input::GetInstance()->GetMousePoint().x;
	float y = Input::GetInstance()->GetMousePoint().y;
if (Clickf[charanum]) {
	CharaSprite[charanum]->SetPosition({ x,y });
	if (!Input::GetInstance()->PushMouseLeft()) {
		Clickf[charanum] = false;
		

	}
}

}
void PlaceObj::PlaceChara(int charanum)
{
	if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), Bench_LU.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (charanum == ONE_GIRL) {
				Benchs[4]->SetCaharaCreate_P(true);
			}
			if (charanum == TWO_CAT) {
				Benchs[4]->SetCaharaCreate_C(true);
			}
			if (charanum == THREE_DOG) {
				Benchs[4]->SetCaharaCreate_D(true);
			}
			if (charanum == FOUR_BIRD) {
				Benchs[4]->SetCaharaCreate_B(true);
			}
			SpriteStartPos(charanum);
		}
	}
	else if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(),Bench_LB.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (charanum == ONE_GIRL) {
				Benchs[5]->SetCaharaCreate_P(true);
			}
			if (charanum == TWO_CAT) {
				Benchs[5]->SetCaharaCreate_C(true);
			}
			if (charanum == THREE_DOG) {
				Benchs[5]->SetCaharaCreate_D(true);
			}
			if (charanum == FOUR_BIRD) {
				Benchs[5]->SetCaharaCreate_B(true);
			}
			SpriteStartPos(charanum);
		}
	}
	else if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(),Bench_RB.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (charanum == ONE_GIRL) {
				Benchs[1]->SetCaharaCreate_P(true);
			}
			if (charanum == TWO_CAT) {
				Benchs[1]->SetCaharaCreate_C(true);
			}
			if (charanum == THREE_DOG) {
				Benchs[1]->SetCaharaCreate_D(true);
			}
			if (charanum == FOUR_BIRD) {
				Benchs[1]->SetCaharaCreate_B(true);
			}
			SpriteStartPos(charanum);
		}
	}
	else if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(),Bench_RU.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (charanum == ONE_GIRL) {
				Benchs[0]->SetCaharaCreate_P(true);
			}
			if (charanum == TWO_CAT) {
				Benchs[0]->SetCaharaCreate_C(true);
			}
			if (charanum == THREE_DOG) {
				Benchs[0]->SetCaharaCreate_D(true);
			}
			if (charanum == FOUR_BIRD) {
				Benchs[0]->SetCaharaCreate_B(true);
			}
			SpriteStartPos(charanum);
		}
	}
}


void PlaceObj::Draw()
{
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Draw();
	}
	Sprite::PreDraw();
	for (int i = 0; i < 4; i++)
	{
		CharaSprite[i]->Draw();
	}
	Sprite::PostDraw();
}
XMVECTOR PlaceObj::wDivision(XMVECTOR vec, XMMATRIX mat)
{
	return vec;
}

void PlaceObj::SpriteStartPos(int charanum)
{
	if (charanum == ONE_GIRL) {
		CharaSprite[charanum]->SetPosition({ 700,200 });
	}
	if (charanum == TWO_CAT) {
		CharaSprite[charanum]->SetPosition({ 700,300 });
	}
	if (charanum == THREE_DOG) {
		CharaSprite[charanum]->SetPosition({ 700,400 });
	}
	if (charanum == FOUR_BIRD) {
		CharaSprite[charanum]->SetPosition({ 700,500 });
	}
}