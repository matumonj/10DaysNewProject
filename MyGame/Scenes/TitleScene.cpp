#include "TitleScene.h"
#include"CameraControl.h"
#include"Input.h"
#include"SceneManager.h"
#include "GameScene.h"

TitleScene::TitleScene(SceneManager* sceneManager) 
	:BaseScene(sceneManager) {
}

void TitleScene::Initialize() {
	Sprite::LoadTexture(11, L"Resources/2d/title.png");

	Sprite* BackGround_ = Sprite::Create(11, { 0,0 });
	BackGround.reset(BackGround_);
	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());

}

void TitleScene::Update() {
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {//押されたら
		BaseScene* scene = new GameScene(sceneManager_);//次のシーンのインスタンス生成
		SceneManager::GetInstance()->SetScene(SceneManager::PLAY);
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
}

void TitleScene::Draw() {
	DirectXCommon::GetInstance()->BeginDraw();//描画コマンドの上らへんに
	Sprite::PreDraw();
	BackGround->Draw();
	Sprite::PostDraw();

	DirectXCommon::GetInstance()->EndDraw();

}

void TitleScene::Finalize() {



}
