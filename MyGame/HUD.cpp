#include "HUD.h"
#include"HUDLayOut.h"
#include"TargetMarker.h"
#include"mHelper.h"
#include"PlayerAttackState.h"
#include"Collision.h"
#include"Player.h"
#include"CameraControl.h"
#include"CustomButton.h"
#include"SceneManager.h"
#include"Input.h"
#include"CustomButton.h"
#include"SelectSword.h"
HUD::~HUD()
{
	delete PlayerHP, EnemyHP_Border, EnemyHP_Inner;
	delete FirstAttackSprite, SecondAttackSprite, ThirdAttackSprite;
	delete coolDownSprite[0], coolDownSprite[1], coolDownSprite[2], coolDownSprite[3], BuffSprite;
	for (int i = 0; i < EnemyHP_Border_Multi.size(); i++) {
		delete EnemyHP_Border_Multi[i], EnemyHP_Inner_Multi[i];
	}

}
HUD* HUD::GetInstance()
{
	static HUD instance;
	return &instance;
}
void HUD::Initialize()
{
	Sprite::LoadTexture(143, L"Resources/quest.png");
	Sprite::LoadTexture(120, L"Resources/bosshp.png");
	TaskSprite= Sprite::Create(143, { 0.0f,-200.0f });
	TaskSprite->SetPosition({ WinApp::window_width/2,WinApp::window_height/2 });
	TaskSprite->SetAnchorPoint({ 0.5,0.5 });
		PlayerHP = Sprite::Create(120, { 0.0f,-200.0f });
	PlayerHP->SetPosition({ 100,100 });
	PlayerHP->SetSize({ 200,200 });
	
	Sprite::LoadTexture(121, L"Resources/bosshp.png");
	Sprite::LoadTexture(20, L"Resources/jump.png");
	Sprite::LoadTexture(21, L"Resources/attack.png");
	Sprite::LoadTexture(22, L"Resources/attack2.png");
	Sprite::LoadTexture(23, L"Resources/barrir.png");
}

void HUD::EnemyHPGaugeInitialize()
{
	Texture::LoadTexture(122, L"Resources/bosshp.png");
	Texture::LoadTexture(123, L"Resources/backright.png");
	Sprite::LoadTexture(12, L"Resources/bosshp.png");
	Sprite::LoadTexture(13, L"Resources/bosshp.png");
	
}
void HUD::SkillButtonInitialize()
{
	FirstAttackSprite = Sprite::Create(20, { CenterPosition.x+100,CenterPosition.y });

	SecondAttackSprite = Sprite::Create(21, { CenterPosition.x,CenterPosition.y+100 });

	ThirdAttackSprite = Sprite::Create(22, { CenterPosition.x-100,CenterPosition.y });

	BuffSprite = Sprite::Create(23, { CenterPosition.x,CenterPosition.y-100 });

	Sprite::LoadTexture(26, L"Resources/cool.png");
	coolDownSprite[0] = Sprite::Create(26, {CenterPosition.x+100+120,CenterPosition.y+ 120 }, { 1,1,1,1 }, { 0.0,1 });
	coolDownSprite[1] = Sprite::Create(26, { CenterPosition.x + 120,CenterPosition.y + 100 + 120 }, { 0,0,0,1 }, { 0.0,1 });
	coolDownSprite[2] = Sprite::Create(26, { CenterPosition.x -100+ 120,CenterPosition.y + 120 }, { 0,0,0,1 }, { 0.0,1 });
	coolDownSprite[3] = Sprite::Create(26, { CenterPosition.x + 120,CenterPosition.y - 100 + 120 }, { 0,0,0,1 }, { 0.0,1 });
	for (int i = 0; i < 4; i++) {
		coolDownSprite[i]->SetSize({ 100,0 });
	}
}

void HUD::EnemyHPGaugeUpdate(std::vector<std::unique_ptr<Enemy>>& enemy)
{

}

void HUD::SkillBottonUpdate()
{
	FirstAttackSprite->SetSize({ 120,120 });
	SecondAttackSprite->SetSize({ 120,120 });
	ThirdAttackSprite->SetSize({ 120,120 });
	BuffSprite->SetSize({ 120,120 });
	
	if (CustomButton::GetInstance()->GetActionButton_JUMP() == CustomButton::BUTTON_B) {
		FirstAttackSprite->SetPosition({ CenterPosition.x + 100,CenterPosition.y });
	}
	else if (CustomButton::GetInstance()->GetActionButton_JUMP() == CustomButton::BUTTON_A) {
		FirstAttackSprite->SetPosition({ CenterPosition.x,CenterPosition.y + 100 });
	}
	else if (CustomButton::GetInstance()->GetActionButton_JUMP() == CustomButton::BUTTON_X) {
		FirstAttackSprite->SetPosition({ CenterPosition.x ,CenterPosition.y-100 });
	}
	else if (CustomButton::GetInstance()->GetActionButton_JUMP() == CustomButton::BUTTON_Y) {
		FirstAttackSprite->SetPosition({ CenterPosition.x-100 ,CenterPosition.y  });
	}

	if (CustomButton::GetInstance()->GetActionButton_ATTACK() == CustomButton::BUTTON_B) {
		SecondAttackSprite->SetPosition({ CenterPosition.x + 100,CenterPosition.y });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK() == CustomButton::BUTTON_A) {
		SecondAttackSprite->SetPosition({ CenterPosition.x,CenterPosition.y + 100 });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK() == CustomButton::BUTTON_X) {
		SecondAttackSprite->SetPosition({ CenterPosition.x ,CenterPosition.y-100 });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK() == CustomButton::BUTTON_Y) {
		SecondAttackSprite->SetPosition({ CenterPosition.x-100,CenterPosition.y  });
	}

	if (CustomButton::GetInstance()->GetActionButton_ATTACK2() == CustomButton::BUTTON_B) {
		ThirdAttackSprite->SetPosition({ CenterPosition.x + 100,CenterPosition.y });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK2() == CustomButton::BUTTON_A) {
		ThirdAttackSprite->SetPosition({ CenterPosition.x,CenterPosition.y + 100 });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK2() == CustomButton::BUTTON_X) {
		ThirdAttackSprite->SetPosition({ CenterPosition.x ,CenterPosition.y-100 });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK2() == CustomButton::BUTTON_Y) {
		ThirdAttackSprite->SetPosition({ CenterPosition.x-100,CenterPosition.y});
	}

	if (CustomButton::GetInstance()->GetActionButton_ATTACK3() == CustomButton::BUTTON_B) {
		BuffSprite->SetPosition({ CenterPosition.x + 100,CenterPosition.y });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK3() == CustomButton::BUTTON_A) {
		BuffSprite->SetPosition({ CenterPosition.x,CenterPosition.y + 100 });
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK3() == CustomButton::BUTTON_X) {
		BuffSprite->SetPosition({ CenterPosition.x ,CenterPosition.y -100});
	} else if (CustomButton::GetInstance()->GetActionButton_ATTACK3() == CustomButton::BUTTON_Y) {
		BuffSprite->SetPosition({ CenterPosition.x-100,CenterPosition.y  });
	}
	//SecondAttackSprite->SetPosition({ CenterPosition.x,CenterPosition.y + 100 });

	coolDownSprite[0]->SetPosition({ CenterPosition.x + 100 + 120,CenterPosition.y + 120 });
	coolDownSprite[1]->SetPosition({ CenterPosition.x + 120,CenterPosition.y + 100 + 120 });
	coolDownSprite[2]->SetPosition({ CenterPosition.x - 100 + 120,CenterPosition.y + 120 });
	coolDownSprite[3]->SetPosition({ CenterPosition.x + 120,CenterPosition.y - 100 + 120 });

	TimeSpeed = 1.0f/SelectSword::GetInstance()->GetSword()->GetCoolTime();
	if (CoolTime_Time >= 1.0f) {
		if (CustomButton::GetInstance()->GetAttackAction()) {
			CoolTime_Time = 0.0f;
		}
	}
	else {
		CoolTime_Time += TimeSpeed;
	}
	for (int i = 0; i < 4; i++) {
		CooltimeSize = { 120, 120 };
		coolDownSprite[i]->SetSize({ CooltimeSize.x,Easing::EaseOut(CoolTime_Time,120,0)});
		coolDownSprite[i]->SetAnchorPoint({ 1,1 });
	}
	if (PlayerAttackState::GetInstance()->GetSkill() != PlayerAttackState::GetInstance()->CoolDown) {
		FirstAttackSprite->setcolor({ 0.5,0.5,0.5,1 });
		SecondAttackSprite->setcolor({ 0.5,0.5,0.5,1 });
		ThirdAttackSprite->setcolor({ 0.5,0.5,0.5,1 });
	}
	if (PlayerAttackState::GetInstance()->GetCoolTime() == 0) {
		FirstAttackSprite->setcolor({ 1,1,1,1 });
		SecondAttackSprite->setcolor({ 1,1,1,1 });
		ThirdAttackSprite->setcolor({ 1,1,1,1 });
	}

}

void HUD::TaskUpdate(DebugCamera* camera)
{
	XMFLOAT3 cPos = camera->GetEye();
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		if (Collision::GetLength(cPos, CameraControl::GetInstance()->CameraPosIndex(2)) < 10) {
			taskfeed = true;
		}
	}
	if (taskfeed) {
		if (taskSpriteSize.x < 800) {
			taskSpriteSize.x += 20;
		}
		taskAlpha += 0.02f;
		if (taskAlpha >= 2.0f) {
			taskfeed = false;
	}
	}
	else {
		taskAlpha -= 0.02f;
	}
	TaskSprite->SetSize({taskSpriteSize.x,1000});
	TaskSprite->setcolor({ 1,1,1,taskAlpha });
	taskAlpha = min(taskAlpha, 2);
	taskAlpha = max(taskAlpha, 0);
}
void HUD::EnemyHPGaugeDraw()
{
}


void HUD::EnemyHPGauge_MultiInitialize()
{
	
}

void HUD::EnemyHPGauge_MultiUpdate(bool &loadf,DebugCamera* camera, std::vector<std::unique_ptr<Enemy>>& enemy)
{
	

	if (loadf) {
		for (int i = 0; i < enemy.size(); i++) {
			EnemyHP_Border_Multi.resize(enemy.size());
			EnemyHP_Inner_Multi.resize(enemy.size());
			multi_NowHP.resize(enemy.size());
			multi_OldHP.resize(enemy.size());
			multi_Hpt.resize(enemy.size());
			multi_sizel.resize(enemy.size());
			
			EnemyHP_Inner_Multi[i] = Texture::Create(122, { 0.0f,-200.0f,1 }, { 1,1,1 } ,{1,1,1,1});
			EnemyHP_Border_Multi[i] = Texture::Create(123, { 0.0f,-200.0f,1 }, { 1,1,1 } ,{ 1,1,1,1 });
			//EnemyHP_Border_Multi[i]->SetPosition({ 80,860,1 });
			EnemyHP_Inner_Multi[i]->CreateTexture();
			EnemyHP_Border_Multi[i]->CreateTexture();
			EnemyHP_Border_Multi[i]->SetAnchorPoint({ 0,0 });
			EnemyHP_Inner_Multi[i]->SetAnchorPoint({ 0,0 });

			}
		loadf = false;
	}

	for (int i = 0; i < enemy.size(); i++) {
		
		//ƒpƒ‰ƒ[ƒ^‚ÌÝ’è
		if (enemy[i] != nullptr && EnemyHP_Border_Multi.size() > 0) {
			if (enemy[i]->GetRecvDamage() == true) {
				multi_NowHP[i] = Percent::GetParcent(enemy[i]->GetMaxHP(), enemy[i]->GetHP())/20.00f ;
				multi_Hpt[i] += 0.001f;
				multi_sizel[i] = { Easing::EaseOut(multi_Hpt[i] ,multi_OldHP[i] ,multi_NowHP[i]),1.5,1 };
				EnemyHP_Inner_Multi[i]->SetScale(multi_sizel[i]);
				if (multi_Hpt[i]>=1.0f) {
					enemy[i]->SetRecvDamage(false);
				}
			} else {
				multi_OldHP[i] =  Percent::GetParcent(enemy[i]->GetMaxHP(),enemy[i]->GetHP()) / 20.00f;
				multi_Hpt[i] = 0;
				EnemyHP_Inner_Multi[i]->SetScale({ Percent::GetParcent(enemy[i]->GetMaxHP(),enemy[i]->GetHP()) / 20.00f,1.5,1 });
			}
			
			
			EnemyHP_Inner_Multi[i]->Update(camera);
			EnemyHP_Border_Multi[i]->Update(camera);
			EnemyHP_Border_Multi[i]->SetScale({2.5,1,1});
			EnemyHP_Border_Multi[i]->SetPosition({ enemy[i]->GetPosition().x-10, enemy[i]->GetPosition().y + 20.0f, enemy[i]->GetPosition().z });

			EnemyHP_Inner_Multi[i]->SetPosition({ EnemyHP_Border_Multi[i]->GetPosition().x,EnemyHP_Border_Multi[i]->GetPosition().y, EnemyHP_Border_Multi[i]->GetPosition().z });
		
		}
	}
}

void HUD::EnemyHPGauge_MultiDraw()
{
	Texture::PreDraw();
	for (int i = 0; i < EnemyHP_Border_Multi.size(); i++) {
		EnemyHP_Border_Multi[i]->Draw();
		EnemyHP_Inner_Multi[i]->Draw();
	}
	Texture::PostDraw();
}
void HUD::SkillBottonDraw()
{
	Sprite::PreDraw();
	FirstAttackSprite->Draw();
	ThirdAttackSprite->Draw();
	BuffSprite->Draw();
	SecondAttackSprite->Draw();

	for (int i = 0; i < 4; i++) {
		coolDownSprite[i]->Draw();
	}
	Sprite::PostDraw();
}
void HUD::Update()
{
	HUDLayOut::GetInstance()->Update();
	PlayerHP->setcolor({ 1,1,1,1 });
}

void HUD::Draw()
{
	Sprite::PreDraw();
	EnemyHPGaugeDraw();
	Sprite::PostDraw();
}

bool HUD::GetLayOutMode()
{
	return HUDLayOut::GetInstance()->GetLayOutMode();
}


void HUD::ChangePosition(XMFLOAT2 MousePosition, XMFLOAT2& c)
{
	float halfsize_x = 50;
	float halfsize_y = 50;

	if (Input::GetInstance()->PushMouseLeft() && Collision::CheckPoint2Rect({ MousePosition.x,MousePosition.y }, { {c.x,c.y},{100,100} }) == true)
	{
		f = true;
	}
	if (f) {
		c = { MousePosition.x - halfsize_x,MousePosition.y - halfsize_y };
		if (Input::GetInstance()->PushMouseLeft() != true) {
			f = false;
		}
	}
}

void HUD::AreaName()
{
	Sprite::PreDraw();
	TaskSprite->Draw();
	Sprite::PostDraw();
}