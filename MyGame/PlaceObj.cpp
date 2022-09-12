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

	CharaSprite[0] = Sprite::Create(21, { 1100,200 });
	CharaSprite[0]->SetSize({ 100,100 });
	CharaSprite[1] = Sprite::Create(21, { 1100,300 });
	CharaSprite[1]->SetSize({ 100,100 });
	CharaSprite[2] = Sprite::Create(21, { 1100,400 });
	CharaSprite[2]->SetSize({ 100,100 });
	CharaSprite[3] = Sprite::Create(21, { 1100,500 });
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

void PlaceObj::Update(Sushi* sushis)
{
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update(sushis);
	}
	DebPos.y = -43;
	obj->SetPosition(DebPos);
	obj->SetScale({ 2,2,2 });
	obj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
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
			if (Bench_LU.schara != NON) { return; }
			if (charanum == ONE_GIRL) {
				Benchs[4]->SetCaharaCreate_P(true);
				Bench_LU.schara = PLAYER;
			}
			if (charanum == TWO_CAT) {
				Benchs[4]->SetCaharaCreate_C(true);
				Bench_LU.schara = CAT;
			}
			if (charanum == THREE_DOG) {
				Benchs[4]->SetCaharaCreate_D(true);
				Bench_LU.schara = DOG;
			}
			if (charanum == FOUR_BIRD) {
				Benchs[4]->SetCaharaCreate_B(true);
				Bench_LU.schara = BIRD;
			}
			SpriteStartPos(charanum);
		}
	}
	
	if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(),Bench_LB.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (Bench_LB.schara != NON) { return; }
			if (charanum == ONE_GIRL) {
				Benchs[5]->SetCaharaCreate_P(true);
				Bench_LB.schara = PLAYER;
			}
			if (charanum == TWO_CAT) {
				Benchs[5]->SetCaharaCreate_C(true);
				Bench_LB.schara = CAT;
			}
			if (charanum == THREE_DOG) {
				Benchs[5]->SetCaharaCreate_D(true);
				Bench_LB.schara = DOG;
			}
			if (charanum == FOUR_BIRD) {
				Benchs[5]->SetCaharaCreate_B(true);
				Bench_LB.schara = BIRD;
			}
			SpriteStartPos(charanum);
		}
	}
	
	 if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(),Bench_RB.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (Bench_RB.schara != NON) { return; }
			if (charanum == ONE_GIRL) {
				Benchs[1]->SetCaharaCreate_P(true);
				Bench_RB.schara = PLAYER;
			}
			if (charanum == TWO_CAT) {
				Benchs[1]->SetCaharaCreate_C(true);
				Bench_RB.schara = CAT;
			}
			if (charanum == THREE_DOG) {
				Benchs[1]->SetCaharaCreate_D(true);
				Bench_RB.schara = DOG;
			}
			if (charanum == FOUR_BIRD) {
				Benchs[1]->SetCaharaCreate_B(true);
				Bench_RB.schara = BIRD;
			}
			SpriteStartPos(charanum);
		}
	}
	
	 if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(),Bench_RU.Position_2d) < 50) {
		if (!Clickf[charanum]) {
			if (Bench_RU.schara!=NON) { return; }
			if (charanum == ONE_GIRL) {
				Benchs[0]->SetCaharaCreate_P(true);
				Bench_RU.schara = PLAYER;
			}
			if (charanum == TWO_CAT) {
				Benchs[0]->SetCaharaCreate_C(true);
				Bench_RU.schara = CAT;
			}
			if (charanum == THREE_DOG) {
				Benchs[0]->SetCaharaCreate_D(true);
				Bench_RU.schara = DOG;
			}
			if (charanum == FOUR_BIRD) {
				Benchs[0]->SetCaharaCreate_B(true);
				Bench_RU.schara = BIRD;
			}
			SpriteStartPos(charanum);
		}
	}
	 //こ　れ　は　ひ　ど　い
	 if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), Bench_LU.Position_2d) >= 50) {
		 if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), Bench_LB.Position_2d) >= 50) {
			 if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), Bench_RU.Position_2d) >= 50) {
				 if (Collision::GetLength2(CharaSprite[charanum]->GetPosition(), Bench_RB.Position_2d) >= 50) {
					 {
						 if (!Clickf[charanum]) {
							 SpriteStartPos(charanum);
						 }
					 }
				 }
			 }
		 }
	 }
}


void PlaceObj::Draw()
{
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Draw();
	}
	obj->PreDraw();
	obj->Draw();
	obj->PostDraw();
	Sprite::PreDraw();
	for (int i = 0; i < 4; i++)
	{
		CharaSprite[i]->Draw();
	}
	Sprite::PostDraw();

	ImGui::Begin("deb");
	ImGui::SliderFloat("x", &DebPos.x, -100, 100);
	ImGui::SliderFloat("y", &DebPos.z, -100, 100);

	ImGui::End();

}
void PlaceObj::SpriteStartPos(int charanum)
{
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

void PlaceObj::LeaveStore()
{
	if (Bench_LB.schara != NON) {
		Bench_LB.LeaveLimit++;
		if (Bench_LB.LeaveLimit >= Bench_LB.LeaveLimit_Max) {
		
		}
	}
}