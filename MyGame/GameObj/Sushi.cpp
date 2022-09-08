#include "Sushi.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
using namespace DirectX;
#define PI 3.14
Sushi::~Sushi()
{

}
void Sushi::TexSet()
{
	//まだファイルつくってないです
	Texture::LoadTexture(1, L"Resources/HP/HP.png");
	HPTex = Texture::Create(1, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	HPTex->CreateTexture();
	HPTex->SetAnchorPoint({ 0,0.5f });
}

void Sushi::TexUp()
{
	HPTex->SetBillboard(true);
	HPTex->SetPosition({ Position.x,Position.y + 10,Position.z });
	HPTex->SetScale({ (float)HP / 20,2,1 });
	HPTex->Update(CameraControl::GetInstance()->GetCamera());
}

void Sushi::TexDraw()
{
	Texture::PreDraw();
	HPTex->Draw();
	Texture::PostDraw();
}
void Sushi::Moves()
{
	switch (SMove)
	{
	case Sushi::GATE:
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
		isDump = Collision::GetLength(Position, GarbagepPos) < 5.0f;
		//回転半径
		if (isDump) {
			SMove = DUMP;
		}
		break;
	case Sushi::DUMP:
		for (int i = 0; i < 5; i++) {
			RotTime[i] = 0;
		}
		Position = GatePos;
		SMove = GATE;
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

void Sushi::Rebirth(int cooltime)
{
	bool CoolEnd = coolTime > cooltime*60;
	if (SMove == DUMP) {
		coolTime++;
		if (CoolEnd) {
			coolTime = 0;
			SMove = CREATE;
		}
	}
	if (SMove == CREATE) {
		Position = GatePos;
	}
}