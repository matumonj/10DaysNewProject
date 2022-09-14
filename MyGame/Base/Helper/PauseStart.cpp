#include"PauseStart.h"
#include "ImageManager.h"
#include <Base/Helper/mHelper.h>


PauseStart::PauseStart() {

}

PauseStart::~PauseStart() {


}

void PauseStart::Init() {
	const int w = 32;
	const int h = 64;
	const int l = 10;
	for (int j = 0; j < 4; j++) {
		num[j] = Sprite::Create(ImageManager::Num, { 0.0f,0.0f });
		int number_index_y = j / l;
		int number_index_x = j % l;
		num[j]->SetTextureRect(
			{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
			{ static_cast<float>(w), static_cast<float>(h) });
		num[j]->SetSize({ w,h });
		num[j]->SetAnchorPoint({ 0.5f,0.5f });
		num[j]->SetSize({ w * 3,h * 3 });
		num[j]->setcolor({ 1.0f,0.0f,0.0f,1.0f });
		num[j]->SetPosition({ (float)980 ,600.0f+(j * 64 )});
	}

	Sprite* Go_ = Sprite::Create(ImageManager::Go, { 1050.0f,650.0f });
	Go.reset(Go_);
}

void PauseStart::Upda() {
	if (ETime[0] <= 1.0f) {
		ETime[0] += 0.02f;
	} else {
		CoolTime++;
	}
	if (ETime[0] >= 1.0f&& CoolTime>30) {
		if (ETime[1] <= 1.0f) {
			//CoolTime = 0;
			ETime[1] += 0.02f;
		} else {
			CoolTime++;
		}
	}
	if (ETime[1] >= 1.0f&& CoolTime> 180) {
		if (ETime[2] <= 1.0f) {
			//CoolTime = 0;
			ETime[2] += 0.02f;
		} else {
			pause = true;
		}
	}





	EaseX[0] = Easing::EaseOut(ETime[0], -1600, 640);
	EaseX[1] = Easing::EaseOut(ETime[1], 1600, 640);
	EaseX[2] = Easing::EaseOut(ETime[2], -500, 360);

	num[3]->SetPosition({ EaseX[0], 360.0f });
	num[2]->SetPosition({ EaseX[1], 360.0f });
	num[1]->SetPosition({ 640.0f, EaseX[2]});

}

void PauseStart::Draw() {
	Sprite::PreDraw();
	for (int i = 1; i < 4; i++) {
		num[i]->Draw();
	}
	Go->Draw();
	Sprite::PostDraw();

}
