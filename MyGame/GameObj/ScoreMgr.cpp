#include "ScoreMgr.h"

ScoreMgr::ScoreMgr() {

}

void ScoreMgr::Init() {
	Sprite::LoadTexture(10, L"Resources/2d/Num.png");
	const int w = 32;
	const int h = 64;
	const int l = 10;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			num[i][j] = Sprite::Create(10, { 0.0f,0.0f });
			int number_index_y = j / l;
			int number_index_x = j % l;
			num[i][j]->SetTextureRect(
				{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
				{ static_cast<float>(w), static_cast<float>(h) });
			num[i][j]->SetSize({ w,h });
			num[i][j]->SetAnchorPoint({ 0,0 });
			num[i][j]->SetSize({ w * 2,h * 2 });
			num[i][j]->setcolor({ 0.0f,0.0f,0.0f,1.0f });
			num[i][j]->SetPosition({ (float)0 ,200.0f });
		}
	}



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
	Sprite::PostDraw();
}
