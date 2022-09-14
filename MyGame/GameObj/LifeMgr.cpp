#include "LifeMgr.h"
#include "ImageManager.h"


LifeMgr* LifeMgr::GetIns() {
	static LifeMgr instans;
	return &instans;
}

void LifeMgr::Init() {
	Sprite* LifeRice_ = Sprite::Create(ImageManager::Rice, { 0.0f,0.0f });
	Sprite* LifeRice2_ = Sprite::Create(ImageManager::Rice, { 0.0f,0.0f });
	Sprite* LifeRice3_ = Sprite::Create(ImageManager::Rice, { 0.0f,0.0f });
	LifeRice[0].reset(LifeRice_);
	LifeRice[1].reset(LifeRice2_);
	LifeRice[2].reset(LifeRice3_);
	for (int i = 0; i < 3; i++) {
		LifeRice[i]->SetAnchorPoint({ 0.5f,0.5f });
	}

}
void LifeMgr::Upda() {
	LifeRice[2]->SetPosition({ 1100,340 });
	LifeRice[1]->SetPosition({ 1100,270 });
	LifeRice[0]->SetPosition({ 1100,200 });
}
void LifeMgr::Draw() {
	Sprite::PreDraw();
	if (life >= 3) {
		LifeRice[2]->Draw();
	}
	if (life >= 2) {
		LifeRice[1]->Draw();
	}
	if (life >= 1) {
		LifeRice[0]->Draw();
	}

	Sprite::PostDraw();
}
