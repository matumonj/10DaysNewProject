#include "MyGame.h"
#include"SceneManager.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include"imgui.h"

void MyGame::Initialize()
{
	Framework::Initialize();
	Sprite::StaticInitialize( WinApp::window_width, WinApp::window_height);
	Audio::GetInstance()->Initialize();
	Audio::GetInstance()->LoadSound(0, "Resources/Audio/bgm_wav/Green.wav");
	Audio::GetInstance()->LoadSound(1, "Resources/Audio/bgm_wav/Sakura.wav");
	Audio::GetInstance()->LoadSound(2, "Resources/Audio/bgm_wav/End.wav");
	ImageManager::GetIns()->Load2D();
	LightGroup::StaticInitialize();
	FbxLoader::GetInstance()->Initialize();
	Texture::StaticInitialize(WinApp::window_width, WinApp::window_height);
	ImageManager::GetIns()->LoadTex2D();
	ModelManager::GetIns()->Initialize();
	//初期シーン
	BaseScene* scene_ = new TitleScene(sceneManger);
	sceneManger->SetnextScene(scene_);

	//Scene->Initialize();
}

void MyGame::Update()
{
	Framework::Update();
}


void MyGame::Draw()
{
	Framework::Draw();
}


//背景スプライト描画　少しめんどくさいやり方 clearDepthBuffer()よみこむため
void MyGame::backGround()
{
	//->BackGround(dxcomn->GetCmdList());
	//dxcomn->ClearDepthBuffer(dxcomn->GetCmdList());
	//Scene->SpritePost(dxcomn->GetCmdList());
}
void MyGame::Finalize()
{
	Framework::Finalize();
}
