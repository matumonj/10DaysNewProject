#include "Sushi.h"
#include"Collision.h"
#include"mHelper.h"
#include"CameraControl.h"
#include"Destroy.h"
#include "ImageManager.h"

using namespace DirectX;
Sushi::~Sushi()
{
	Destroy_unique(SushiObj);
}
void Sushi::TexSet()
{
	HPTex = Texture::Create(ImageManager::Sushi, { 0,0,0 }, { 0,0,0 }, { 1,1,1,1 });
	HPTex->CreateTexture();
	HPTex->SetAnchorPoint({ 0,0.5f });
}

void Sushi::TexUp()
{
	if (SushiObj != nullptr) {
		HPTex->SetBillboard(true);
		HPTex->SetPosition({ Position.x,Position.y + 3,Position.z });
		HPTex->SetScale({Percent::GetParcent((float)MaxHP,(float)HP)/40.0f,1,1});
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
