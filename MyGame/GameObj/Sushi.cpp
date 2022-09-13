#include "Sushi.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
#include"Destroy.h"
using namespace DirectX;
Sushi::~Sushi()
{
	Destroy_unique(SushiObj);
}
void Sushi::TexSet()
{
	//‚Ü‚¾ƒtƒ@ƒCƒ‹‚Â‚­‚Á‚Ä‚È‚¢‚Å‚·
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
		HPTex->SetScale({Percent::GetParcent(MaxHP,HP)/40.0f,1,1});
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
void Sushi::Moves(Wave wave)
{
	
}

void Sushi::RotState()
{

}

void Sushi::RotState3()
{
	/*if (Collision::GetLength(Position, { 20,0,10}) < 1.0f) {
		RotTime[0] += 0.2f;
		if (RotTime[0] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[0], -90, 0);
		}
	}
	if (Collision::GetLength(Position, { 20,0,15 }) < 1.0f) {
		RotTime[1] += 0.2f;
		if (RotTime[1] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[1], 0, -90);
		}
	}
	if (Collision::GetLength(Position, { -20,0,15 }) < 1.0f) {
		RotTime[2] += 0.2f;
		if (RotTime[2] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[2], -90, -180);
		}
	}
	if (Collision::GetLength(Position, { -20,0,5 }) < 1.0f) {
		RotTime[3] += 0.2f;
		if (RotTime[3] <= 1.0f) {
			Rot.y = Easing::EaseOut(RotTime[3], -180, -270);
		}
	}*/
}
