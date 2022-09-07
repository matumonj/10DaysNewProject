#include "ConfigSprite.h"

ConfigSprite* ConfigSprite::GetInstance()
{
	static ConfigSprite instance;

	return &instance;
}
ConfigSprite::~ConfigSprite()
{
	delete RayOutSprite, EnemyHPSelectSprite;
	delete MenuSprite, SwordSelectSprite;
}
void ConfigSprite::Initialize()
{
	Sprite::LoadTexture(121, L"Resources/03 ŠJ•ÂŒ^ƒƒjƒ…[/bg_menu.png");
	Sprite::LoadTexture(122, L"Resources/layout.png");
	Sprite::LoadTexture(123, L"Resources/custom.png");
	Sprite::LoadTexture(124, L"Resources/swordselect.png");

	MenuSprite = Sprite::Create(121, { 1,1 });
	RayOutSprite = Sprite::Create(122, { 1,1 });
	EnemyHPSelectSprite = Sprite::Create(123, { 1,1 });
	SwordSelectSprite = Sprite::Create(124, { 1,1 });
	RayOutSprite->SetAnchorPoint({ 0.5f,0.5f });
	EnemyHPSelectSprite->SetAnchorPoint({ 0.5f,0.5f });
	SwordSelectSprite->SetAnchorPoint({ 0.5f,0.5f });
	RayOutSprite->SetPosition(SpritePosition[0]);
	EnemyHPSelectSprite->SetPosition(SpritePosition[1]);
	SwordSelectSprite->SetPosition(SpritePosition[2]);
	MenuSprite->SetSize({ 600,600 });
	RayOutSprite->SetSize({ 600,600 });
	EnemyHPSelectSprite->SetSize({ 600,600 });
	SwordSelectSprite->SetSize({ 600,600 });
}

void ConfigSprite::Update()
{

}

void ConfigSprite::Draw()
{
	//Sprite::PreDraw();
	MenuSprite->Draw();
	RayOutSprite->Draw();
	EnemyHPSelectSprite->Draw();
	SwordSelectSprite->Draw();
	//Sprite::PostDraw();
}