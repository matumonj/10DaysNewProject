#include "LifeMgr.h"
#include "ImageManager.h"
LifeMgr* LifeMgr::GetIns() {
	static LifeMgr instans;
	return &instans;
}

void LifeMgr::Init() {
	Sprite* LifeRice_ = Sprite::Create(ImageManager::Rice, { 0.0f,0.0f });

	for (int i = 0; i < 3; i++) {
		LifeRice_->SetAnchorPoint({ 0.5f,0.5f });
		LifeRice[i].reset(LifeRice_);
	}
	LifeRice[0]->SetPosition({ 1000,200 });
	LifeRice[1]->SetPosition({ 1000,400 });
	LifeRice[2]->SetPosition({ 1000,600 });
}
void LifeMgr::Upda() {


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
