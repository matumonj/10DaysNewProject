#include"PauseStart.h"
#include "ImageManager.h"
#include <Base/Helper/mHelper.h>


PauseStart::PauseStart() {

}

PauseStart::~PauseStart() {


}

void PauseStart::Init() {
	num[1] = Sprite::Create(ImageManager::Count1, { -640.0f,360.0f });
	num[1]->SetAnchorPoint({ 0.5f,0.5f });
	num[2] = Sprite::Create(ImageManager::Count2, { -640.0f,360.0f });
	num[2]->SetAnchorPoint({ 0.5f,0.5f });
	num[3] = Sprite::Create(ImageManager::Count3, { -640.0f,360.0f });
	num[3]->SetAnchorPoint({ 0.5f,0.5f });

	Sprite* Go_ = Sprite::Create(ImageManager::Go, { 640.0f,360.0f });
	Go_->SetAnchorPoint({ 0.5f,0.5f });
	Go_->setcolor({ 1.0f,1.0f,1.0f,0.0f });
	Go.reset(Go_);
}

void PauseStart::Upda() {
	if (ETime[0] <= 1.0f) {
		fase = 0;
		ETime[0] += 0.02f;
	} else {
		CoolTime[0]++;
	}
	if (ETime[0] >= 1.0f&& CoolTime[0] >30) {
		if (ETime[1] <= 1.0f) {
			fase = 1;
			ETime[1] += 0.02f;
		} else {
			CoolTime[1]++;
		}
	}
	if (ETime[1] >= 1.0f&& CoolTime[1] > 30) {
		if (ETime[2] <= 1.0f) {
			fase = 2;
			ETime[2] += 0.02f;
		} else {
			CoolTime[2]++;
		}
	}
	if (CoolTime[2] > 30) {
		if (ETime[3] <= 1.0f) {
			fase = 3;
			ETime[3] += 0.02f;
		} else {
			CoolTime[3]++;
		}
	}
	if (CoolTime[3] > 30) {
		pause = true;
	}


	EaseX[0] = Easing::EaseOut(ETime[0], 1280+320, 640);
	EaseX[1] = Easing::EaseOut(ETime[1], 0-320, 640);
	EaseX[2] = Easing::EaseOut(ETime[2], -500, 360);
	EaseX[3] = Easing::EaseOut(ETime[3], 0, 1);

	num[3]->SetPosition({ EaseX[0], 360.0f });
	num[2]->SetPosition({ EaseX[1], 360.0f });
	num[1]->SetPosition({ 640.0f, EaseX[2]});
	Go->setcolor({ 1.0f,1.0f,1.0f,EaseX[3]});

}

void PauseStart::Draw() {
	if (pause) { return; }
	Sprite::PreDraw();
	if (fase!=3) {
		num[3 - fase]->Draw();
	} else {
		Go->Draw();
	}
	Sprite::PostDraw();

}
