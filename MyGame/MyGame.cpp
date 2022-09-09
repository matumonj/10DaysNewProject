#include "MyGame.h"
#include"SceneManager.h"
#include"imgui.h"
void MyGame::Initialize()
{
	Framework::Initialize();
	Sprite::StaticInitialize( WinApp::window_width, WinApp::window_height);
	LightGroup::StaticInitialize();
	FbxLoader::GetInstance()->Initialize();
	Texture::StaticInitialize(WinApp::window_width, WinApp::window_height);
	//Scene = new TitleScene();
	//初期シーン
	BaseScene* scene_ = new ResultScene(sceneManger);
	//SceneManager::GetInstance()->SetScene(SceneManager::TITLE);
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
