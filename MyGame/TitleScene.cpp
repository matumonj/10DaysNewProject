#include "TitleScene.h"
#include"Input.h"
#include"SceneManager.h"
#include"Tutorial.h"
#include"Feed.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	Sprite::LoadTexture(3, L"Resources/title.png");
	titlesprite = Sprite::Create(3, { 0.0f,0.0f });

	Sprite::LoadTexture(4, L"Resources/title2.png");
	titlesprite2 = Sprite::Create(4, {  WinApp::window_width / 2,0.0f });
	Feed::GetInstance()->initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{ 
	if (Input::GetInstance()->TriggerButton(Input::Button_B)) {//押されたら
		BaseScene* scene = new Tutorial(sceneManager_);//次のシーンのインスタンス生成
		SceneManager::GetInstance()->SetScene(SceneManager::TUTORIAL);
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
	//titlesprite2->SetRotation(180);
	titlesprite->SetSize({ WinApp::window_width/2,WinApp::window_height });
	titlesprite2->SetSize({ WinApp::window_width / 2,WinApp::window_height });
}

/// <summary>
/// スプライト描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw()
{
	Sprite::PreDraw();
	titlesprite2->Draw();
	titlesprite->Draw();
	Sprite::PostDraw();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw()
{
	//ポストエフェクトの描画
	DirectXCommon::GetInstance()->BeginDraw();//描画コマンドの上らへんに
	SpriteDraw();
	
	DirectXCommon::GetInstance()->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}