#include "Sushi.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
#include"Destroy.h"
using namespace DirectX;
#define PI 3.14
Sushi::~Sushi()
{
	Destroy_unique(SushiObj);
}
void Sushi::TexSet()
{
	//まだファイルつくってないです
	Texture::LoadTexture(1, L"Resources/2d/SushiHP/HP.png");
	HPTex = Texture::Create(1, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	HPTex->CreateTexture();
	HPTex->SetAnchorPoint({ 0,0.5f });
}

void Sushi::TexUp()
{
	if (SushiObj != nullptr) {
		HPTex->SetBillboard(true);
		HPTex->SetPosition({ Position.x,Position.y + 3,Position.z });
		HPTex->SetScale({ (float)HP / 20,1,1 });
		HPTex->Update(CameraControl::GetInstance()->GetCamera());
	}
}

void Sushi::TexDraw()
{
	if (SushiObj) {
		Texture::PreDraw();
		HPTex->Draw();
		Texture::PostDraw();
	}
}
void Sushi::Moves(int cooltime)
{
	switch (SMove)
	{
	case Sushi::GATE:
		Rot.y = 0;
		Position = GatePos;
			SMove = LANE;
		break;
	case Sushi::LANE:
		//移動ベクトルをy軸周りの角度で回転
		RotState();
		move = { 0,0,0.1f,0 };

		matRot = XMMatrixRotationY(XMConvertToRadians(Rot.y));

		move = XMVector3TransformNormal(move, matRot);

		Position={Position.x + move.m128_f32[0],Position.y,	Position.z + move.m128_f32[2] };
		//廃棄条件
		isDump = Collision::GetLength(Position, GarbagepPos) < 2.0f;
		//回転半径
		if (isDump) {
			SMove = DUMP;
		}
		break;
	case Sushi::DUMP:
		for (int i = 0; i < 5; i++) {
			RotTime[i] = 0;
		}
		Position.y -=0.2f;
		if (Position.y < -10) {
			SMove = DEAD;
		}
		break;
	case Sushi::DEAD:
		Scale.x -= 0.2f;
		Scale.y -= 0.2f;
		Scale.z -= 0.2f;
		if (Scale.x<0) {
			//delete HPTex;
			//Destroy_unique(SushiObj);
		}
		break;
	default:
		break;
	}
	
}

void Sushi::RotState()
{
	if (Collision::GetLength(Position, { 0,0,5 }) < 1.0f) {
		RotTime[0] += 0.2f;
		if (RotTime[0] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[0], 0, 90);
		}
	}
	if (Collision::GetLength(Position, { 20,0,5 }) < 1.0f) {
		RotTime[1] += 0.2f;
		if (RotTime[1] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[1], 90, 0);
		} 
	}
	if (Collision::GetLength(Position, { 20,0,15 }) <1.0f) {
		RotTime[2] += 0.2f;
		if (RotTime[2] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[2], 0, -90);
		} 
	}
	if (Collision::GetLength(Position, { -20,0,15 }) < 1.0f) {
		RotTime[3] += 0.2f;
		if (RotTime[3] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[3], -90, -180);
		} 
	}
	if (Collision::GetLength(Position, { -20,0,5 }) < 1.0f) {
		RotTime[4] += 0.2f;
		if (RotTime[4] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[4], -180, -270);
		} 
	}
}
