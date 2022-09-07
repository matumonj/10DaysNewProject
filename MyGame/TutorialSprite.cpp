#include "TutorialSprite.h"
#include"CustomButton.h"
#include"SistemConfig.h"
#include"EnemyControl.h"
#include"FenceControl.h"
#include"ChestControl.h"
#include"mHelper.h"
TutorialSprite* TutorialSprite::GetInstance()
{
	static TutorialSprite instance;
	return &instance;
}
void TutorialSprite::Initialize()
{
	input = Input::GetInstance();
	Sprite::LoadTexture(171, L"Resources/tutorial1.png");
	Sprite::LoadTexture(172, L"Resources/tutorial2.png");
	Sprite::LoadTexture(173, L"Resources/tutorial3.png");
	Sprite::LoadTexture(174, L"Resources/tutorial4.png");
	Sprite::LoadTexture(175, L"Resources/tutorial5.png");
	Sprite::LoadTexture(176, L"Resources/tutorial6.png");
	Sprite::LoadTexture(170, L"Resources/Tuto");
	Task[HELLO] = Sprite::Create(171, { 10,10 });
	Task[WALK] = Sprite::Create(172, { 10,10 });
	Task[SETTING] = Sprite::Create(173, { 10,10 });
	Task[ATTACK] = Sprite::Create(174, { 10,10 });
	Task[GETKEY] = Sprite::Create(175, { 10,10 });
	Task[CLEAR] = Sprite::Create(176, { 10,10 });
	for (int i = 0; i < TaskNum; i++) {
		Task[i]->SetAnchorPoint({ 0,0 });
		SpriteSizeX[i] = 0;
	}

	task = THELLO;
}

void TutorialSprite::Update()
{
	//移動とジャンプ
	if (input->LeftTiltStick(input->Down) || input->LeftTiltStick(input->Up) || input->LeftTiltStick(input->Left) || input->LeftTiltStick(input->Right)) {
		Movement++;
	}
	if (CustomButton::GetInstance()->GetJumpAction() == true) {
		Jump = true;
	}

	//歩きとジャンプ
	ClearWalk = Movement > 30 && Jump == true;
	//セッティング
	if (SistemConfig::GetInstance()->GetEndConfig()) {
		ClearSetting =true ;
	}
	//攻撃
	if (EnemyControl::GetInstance()->GetTutorialEnemyindex()[0] != nullptr) {
		ClearAttack = EnemyControl::GetInstance()->GetTutorialEnemyindex()[0]->GetHP() <= 0;
	}
	//オールコンプリート
	AllTaskClear = ClearWalk && ClearAttack && ClearSetting;
	//チュートリアルの宝箱
	GetChest = ChestControl::GetInstance()->GetTutorialChest() == true;

	FenceControl::GetInstance()->SetTutorialFenceOpen(AllTaskClear);

	switch (task)
	{
	case TutorialSprite::THELLO:
		if (MassageCheck[HELLO]) {
			//次のタスクへの条件(３引数)
			NextTask(t[HELLO], TMOVE, true);
		}
		//説明スプライトの拡縮
		Ease_SpriteSize_Up(SpriteSizeX[HELLO], t[HELLO], HELLO);
		break;

	case TutorialSprite::TMOVE:
		if (MassageCheck[WALK]) {
			NextTask(t[WALK], TSETTING, ClearWalk);
		}

		Ease_SpriteSize_Up(SpriteSizeX[WALK], t[WALK], WALK);
		break;

	case TutorialSprite::TSETTING:
		if (MassageCheck[SETTING]) {
			NextTask(t[SETTING], TATTACK, ClearSetting);
		}

		Ease_SpriteSize_Up(SpriteSizeX[SETTING], t[SETTING], SETTING);
		break;
	case TutorialSprite::TATTACK:
		if (MassageCheck[ATTACK]) {
			NextTask(t[ATTACK], TGETKEY, ClearAttack);
		}

		Ease_SpriteSize_Up(SpriteSizeX[ATTACK], t[ATTACK], ATTACK);
		break;
	case TutorialSprite::TGETKEY:
		if (MassageCheck[GETKEY]) {
			NextTask(t[GETKEY], TEND, GetChest);
		}

		Ease_SpriteSize_Up(SpriteSizeX[GETKEY], t[GETKEY], GETKEY);
		break;
	case TutorialSprite::TEND:
		if (MassageCheck[CLEAR]) {
			NextTask(t[CLEAR],THELLO,false);
		}

		Ease_SpriteSize_Up(SpriteSizeX[CLEAR], t[CLEAR], CLEAR);
		break;
	default:
		break;
	}
	for (int i = 0; i < TaskNum; i++) {
		Task[i]->SetSize({ SpriteSizeX[i],1600 });
	}
}

void TutorialSprite::Draw()
{
	Sprite::PreDraw();
	for (int i = 0; i < TaskNum; i++) {
		Task[i]->Draw();
	}
	Sprite::PostDraw();
}

void TutorialSprite::Ease_SpriteSize_Up(float& x, float& t, int index)
{

	if (input->TriggerButton(input->Button_A)) {
		MassageCheck[index] = true;
	}
	if (MassageCheck[index]) {
		x = Easing::EaseOut(t, 0, 1800);
		if (t >= 0.0f) {
			t -= 0.05f;
		}
	} else {
		x = Easing::EaseOut(t, 0, 1800);
		if (t <= 1.0f) {
			t += 0.05f;
		}
	}
}

void TutorialSprite::NextTask(float t, TaskMenu nexttask, bool nextjudg)
{
	if (t <= 0.0f) {
		if (nextjudg) {
			task = nexttask;
		}
	}
}

TutorialSprite::~TutorialSprite()
{
	for (int i = 0; i < TaskNum; i++) {
		delete Task[i];
	}
	
}