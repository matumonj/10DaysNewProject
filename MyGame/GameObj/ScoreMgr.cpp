#include "ScoreMgr.h"
#include "ImageManager.h"
ScoreMgr::ScoreMgr() {

}

void ScoreMgr::Init() {
	const int w = 32;
	const int h = 64;
	const int l = 10;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			num[i][j] = Sprite::Create(ImageManager::Num, { 0.0f,0.0f });
			int number_index_y = j / l;
			int number_index_x = j % l;
			num[i][j]->SetTextureRect(
				{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
				{ static_cast<float>(w), static_cast<float>(h) });
			num[i][j]->SetSize({ w,h });
			num[i][j]->SetAnchorPoint({ 0,0 });
			num[i][j]->SetSize({ w * 2,h * 2 });
			num[i][j]->setcolor({ 1.0f,0.0f,0.0f,1.0f });
			num[i][j]->SetPosition({ (float)980 - (70.0f * i) ,600.0f });
		}
	}
	Sprite* Doll_ = Sprite::Create(ImageManager::Doll, { 1050.0f,650.0f });
	Doll.reset(Doll_);



}
void ScoreMgr::Upda() {

	First.clear();
	for (int tmp = score; tmp > 0;) {
		First.push_back(tmp % 10);
		tmp /= 10;
	}

}
void ScoreMgr::Draw() {
	Sprite::PreDraw();

	for (int i = 0; i < First.size() && i < 5; i++) {
		num[i][(int)First[i]]->Draw();
	}
	Doll->Draw();
	Sprite::PostDraw();
}
