#include "SelectSword.h"
#include"BigSword.h"
#include"SmallSword.h"
#include"NormalSword.h"
#include"CameraControl.h"
#include"mHelper.h"
SelectSword::~SelectSword()
{
	delete SwordSample[0], SwordSample[1], SwordSample[2], Frame;
}
SelectSword* SelectSword::GetInstance()
{
	static SelectSword instance;
	return &instance;
}
void SelectSword::Initialize()
{
	Sword = std::make_unique<NormalSword>();
	Sword->Initialize(CameraControl::GetInstance()->GetCamera());
	Sprite::LoadTexture(230, L"Resources/smallSwordtex.png");
	Sprite::LoadTexture(231, L"Resources/normalSwordtex.png");
	Sprite::LoadTexture(232, L"Resources/bigSwordtex.png");

	Sprite::LoadTexture(233, L"Resources/jump.png");
	SwordSample[0] = Sprite::Create(230, { 1,1 });
	SwordSample[1] = Sprite::Create(231, { 1,1 });
	SwordSample[2] = Sprite::Create(232, { 1,1 });
	Frame = Sprite::Create(233, { 1,1 });
	for (int i = 0; i < 3; i++) {
		//フィールドにモデル割り当て
		//SwordSample[i]->Initialize();
		SwordSample[i]->SetSize({ 200,200 });
		SwordSample[i]->SetAnchorPoint({ 0.5,0.5 });
		SwordSample[i]->SetPosition({ Position[i] });
	}
	Frame->SetSize({ 250,250 });
	Frame->SetPosition(Position[0]);
	Frame->SetAnchorPoint({ 0.5,0.5 });
	input = Input::GetInstance();
}
void SelectSword::SetSmallSword(SwordScale nowsword)
{
	switch (nowsword)
	{
	case SelectSword::SMALL:
		Sword = std::make_unique<SmallSword>();
		break;
	case SelectSword::NORMAL:
		Sword = std::make_unique<NormalSword>();
		break;
	case SelectSword::BIG:
		Sword = std::make_unique<BigSword>();
		break;
	default:
		break;
	}
	//
	//Sword = std::make_unique<SmallSword>();
	Sword->Initialize(CameraControl::GetInstance()->GetCamera());
}

void SelectSword::Update()
{
	if (SelectJudg) {
		if (input->TriggerCrossKey(input->Cross_Right)) {
			index++;
		} else if (input->TriggerCrossKey(input->Cross_Left)) {
			index--;
		}

		if (index == 0) {
			NowSelectSword = SMALL;
		} else if (index == 1) {
			NowSelectSword = NORMAL;
		} else if (index == 2) {
			NowSelectSword = BIG;
		}
		if (input->TriggerButton(input->Button_A)) {
			SetSmallSword(NowSelectSword);
		}
		Frame->SetPosition(Position[index]);
	}
	//else {
		Sword->Update(CameraControl::GetInstance()->GetCamera());
	//}
	index = min(index, 2);
	index = max(index, 0);
}

void SelectSword::Draw()
{
	if (SelectJudg) {
		Sprite::PreDraw();
		for (int i = 0; i < 3; i++) {
			SwordSample[i]->Draw();
		}
		Frame->Draw();
		Sprite::PostDraw();
	}
	
}

void SelectSword::SwordDraw()
{
	Sword->Draw();
}