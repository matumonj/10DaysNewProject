#include "AttackCollision.h"
#include"PlayerControl.h"
#include"CameraControl.h"
#include"EnemyControl.h"
#include"Collision.h"
#include"CustomButton.h"
#include"SceneManager.h"
AttackCollision* AttackCollision::GetInstance()
{
	static AttackCollision instance;
	return &instance;
}
void AttackCollision::Init()
{
	cModel = Model::CreateFromOBJ("chest");
	cObj = new Object3d();
	cObj->Initialize(CameraControl::GetInstance()->GetCamera());
	cObj->SetModel(cModel);
	Position = { PlayerControl::GetInstance()->GetPlayer()->GetPosition().x,
	PlayerControl::GetInstance()->GetPlayer()->GetPosition().y,
	PlayerControl::GetInstance()->GetPlayer()->GetPosition().z };
	input = Input::GetInstance();
}

void AttackCollision::Update()
{

	if (input->Pushkey(DIK_W) || input->Pushkey(DIK_A) || input->Pushkey(DIK_D) || input->Pushkey(DIK_S)
		|| (input->LeftTiltStick(input->Left) || input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Up) || input->LeftTiltStick(input->Down))) {
		Position.x += PlayerControl::GetInstance()->GetPlayer()->GetMove().m128_f32[0] * 3;
		Position.z += PlayerControl::GetInstance()->GetPlayer()->GetMove().m128_f32[2] * 3;
	}

	AttackArea.position = { Position.x,Position.z };
	AttackArea.scale = { 30,30 };

	//デバッグ用


	cObj->SetScale({ 5,5,5 });
	cObj->SetPosition(Position);
	cObj->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
}

void AttackCollision::GetCol(int damage)
{

	switch (SceneManager::GetInstance()->GetScene())
	{
	case SceneManager::TUTORIAL:
		EnemyArea.resize(1);
		EnemyArea[0].position = { EnemyControl::GetInstance()->GetTutorialEnemyindex()[0]->GetPosition().x,
		EnemyControl::GetInstance()->GetTutorialEnemyindex()[0]->GetPosition().z };
		EnemyArea[0].scale = { 30,30 };
		for (int i = 0; i < EnemyArea.size(); i++) {
			if (Collision::CheckBox2Box(AttackArea, EnemyArea[i]) == true) {
				if (CustomButton::GetInstance()->GetAttackAction()) {
					EnemyControl::GetInstance()->GetTutorialEnemyindex()[i]->Setcol({ 0,1,0,1 });
					EnemyControl::GetInstance()->GetTutorialEnemyindex()[i]->RecvDamage(damage);
					//break;
				} else {
					EnemyControl::GetInstance()->GetTutorialEnemyindex()[i]->Setcol({ 1,1,1,1 });
				}
			} else if (Collision::CheckBox2Box(AttackArea, EnemyArea[i]) == false) {
				EnemyControl::GetInstance()->GetTutorialEnemyindex()[0]->Setcol({ 1,1,1,1 });
			}
		}
		break;

	case SceneManager::PLAY:
		EnemyArea.resize(EnemyControl::GetInstance()->GetEnemyindex(0).size());
		for (int i = 0; i < EnemyArea.size(); i++) {
			EnemyArea[i].position = { EnemyControl::GetInstance()->GetEnemyindex(0)[i]->GetPosition().x,
			EnemyControl::GetInstance()->GetEnemyindex(0)[i]->GetPosition().z };
			EnemyArea[i].scale = { 10,10 };
		}
		for (int i = 0; i < EnemyArea.size(); i++) {
			if (Collision::CheckBox2Box(AttackArea, EnemyArea[i]) == true) {
				if (CustomButton::GetInstance()->GetAttackAction()) {
					EnemyControl::GetInstance()->GetEnemyindex(0)[i]->Setcol({ 0,1,0,1 });
					EnemyControl::GetInstance()->GetEnemyindex(0)[i]->RecvDamage(damage);
					break;
				} else {
					EnemyControl::GetInstance()->GetEnemyindex(0)[i]->Setcol({ 1,1,1,1 });
				}
			} else if (Collision::CheckBox2Box(AttackArea, EnemyArea[i]) == false) {
				EnemyControl::GetInstance()->GetEnemyindex(0)[i]->Setcol({ 1,1,1,1 });
			}
		}
		break;

	case SceneManager::BOSS:
		EnemyArea.resize(1);
		EnemyArea[0].position = { EnemyControl::GetInstance()->GetBossEnemyindex()[0]->GetPosition().x,
		EnemyControl::GetInstance()->GetBossEnemyindex()[0]->GetPosition().z };
		EnemyArea[0].scale = { 10,10 };
		for (int i = 0; i < EnemyArea.size(); i++) {
			if (EnemyControl::GetInstance()->GetBossEnemyindex()[0] != nullptr) {
				if (Collision::CheckBox2Box(AttackArea, EnemyArea[i]) == true) {
					if (CustomButton::GetInstance()->GetAttackAction()) {
						EnemyControl::GetInstance()->GetBossEnemyindex()[i]->Setcol({ 0,1,0,1 });
						EnemyControl::GetInstance()->GetBossEnemyindex()[i]->RecvDamage(damage);
						//break;
					} else {
						EnemyControl::GetInstance()->GetBossEnemyindex()[i]->Setcol({ 1,1,1,1 });
					}
				} else if (Collision::CheckBox2Box(AttackArea, EnemyArea[i]) == false) {
					EnemyControl::GetInstance()->GetBossEnemyindex()[0]->Setcol({ 1,1,1,1 });
				}
			}
		}
		break;
	default:
		break;
	}
}
void AttackCollision::Draw()
{
	cObj->PreDraw();
	cObj->Draw();
	cObj->PostDraw();
}