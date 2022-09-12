#include "TitleScene.h"
#include"Input.h"
#include"SceneManager.h"
#include "GameScene.h"
#include"Tuna.h"
#include "Egg.h"

TitleScene::TitleScene(SceneManager* sceneManager) 
	:BaseScene(sceneManager) {
}

void TitleScene::Initialize() {
	Sprite::LoadTexture(11, L"Resources/2d/title.png");
	Sprite* BackGround_ = Sprite::Create(11, { 0,0 });
	BackGround.reset(BackGround_);

	sushis.push_back(new Tuna());
	sushis.push_back(new Egg());
	sushis.push_back(new Tuna());
	sushis.push_back(new Egg());
	sushis.push_back(new Tuna());

	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->SetPos({ i * 5.0f,-20.0f,0 });
			sushis[i]->Initialize();
	}

	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

}

void TitleScene::Update() {
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->TitleUpda();

	}
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
	DirectXCommon::GetInstance()->ClearDepthBuffer();
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->Draw();
	}

	DirectXCommon::GetInstance()->EndDraw();

}

void TitleScene::Finalize() {



}
