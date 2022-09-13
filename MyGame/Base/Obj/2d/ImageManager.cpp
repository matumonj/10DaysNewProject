#include "ImageManager.h"

ImageManager* ImageManager::GetIns() {
	static ImageManager instans;
	return &instans;
}

void ImageManager::Load2D() {
	// テクスチャ読み込み
	Sprite::LoadTexture(Wave1, L"Resources/2d/Wave/wave1.png");
	Sprite::LoadTexture(Wave2, L"Resources/2d/Wave/wave2.png");
	Sprite::LoadTexture(Wave3, L"Resources/2d/Wave/wave3.png");
	Sprite::LoadTexture(Wave4, L"Resources/2d/Wave/wave4.png");
	Sprite::LoadTexture(Num, L"Resources/2d/Num.png");
	Sprite::LoadTexture(BG, L"Resources/2d/BG.png");
	Sprite::LoadTexture(Doll, L"Resources/2d/Doll.png");
	Sprite::LoadTexture(IconGirl, L"Resources/2d/CharaIcon/girl.png");
	Sprite::LoadTexture(IconCat, L"Resources/2d/CharaIcon/cat.png");
	Sprite::LoadTexture(IconInu, L"Resources/2d/CharaIcon/inu.png");
	Sprite::LoadTexture(IconBack, L"Resources/2d/CharaIcon/charaIconB.png");
	Sprite::LoadTexture(Target, L"Resources/target.png");
	Sprite::LoadTexture(White, L"Resources/white1x1.png");
	Sprite::LoadTexture(Result, L"Resources/2d/Result.png");
	Sprite::LoadTexture(Title, L"Resources/2d/title.png");
	Sprite::LoadTexture(Black, L"Resources/2d/Blackfilter.png");
}

void ImageManager::LoadTex2D() {
	// テクスチャ読み込み
	Texture::LoadTexture(Sushi, L"Resources/2d/SushiHP/HP.png");
}

