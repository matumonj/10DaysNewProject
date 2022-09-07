#include "Feed.h"
#include"WinApp.h"
Feed* Feed::GetInstance()
{
	static Feed instance;
	return &instance;
}
Feed::~Feed()
{
	delete FeedSprite;
}
void Feed::initialize()
{
	Sprite::LoadTexture(150, L"Resources/white1x1.png");
	FeedSprite = Sprite::Create(150, { 0,0 });
	FeedSprite->SetSize({WinApp::window_width, WinApp::window_height
});
}

void Feed::Update_White(feedtype type)
{
	if (type == FEEDIN) {
		feedalpha += 0.01f;
	}
	else {
		feedalpha -= 0.01f;
	}
	rgbcolor = { 1,1,1 };
	feedalpha = max(feedalpha, 0);
	feedalpha = min(feedalpha, 1);
}


void Feed::Update_Black(feedtype type)
{
	if (type == FEEDIN) {
		feedalpha += 0.01f;
	} else {
		feedalpha -= 0.01f;
	}
	rgbcolor = { 0,0,0 };
	feedalpha = max(feedalpha, 0);
	feedalpha = min(feedalpha, 1);
}

void Feed::Draw()
{
	FeedSprite->setcolor({ rgbcolor.x,rgbcolor.y,rgbcolor.z,feedalpha });
	Sprite::PreDraw();
	FeedSprite->Draw();
	Sprite::PostDraw();
}