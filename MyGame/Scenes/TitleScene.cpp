#include "TitleScene.h"
#include"Input.h"
#include"SceneManager.h"
#include "GameScene.h"
#include"Tuna.h"

TitleScene::TitleScene(SceneManager* sceneManager) 
	:BaseScene(sceneManager) {
}

void TitleScene::Initialize() {
	Sprite::LoadTexture(11, L"Resources/2d/title.png");
	Sprite* BackGround_ = Sprite::Create(11, { 0,0 });
	BackGround.reset(BackGround_);

	sushis.push_back(new Tuna());
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->Initialize();

	}

	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

}

void TitleScene::Update() {
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->Update();

	}
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {//�����ꂽ��
		BaseScene* scene = new GameScene(sceneManager_);//���̃V�[���̃C���X�^���X����
		SceneManager::GetInstance()->SetScene(SceneManager::PLAY);
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
}

void TitleScene::Draw() {
	DirectXCommon::GetInstance()->BeginDraw();//�`��R�}���h�̏��ւ��
	Sprite::PreDraw();
	BackGround->Draw();
	Sprite::PostDraw();
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->Draw();
	}

	DirectXCommon::GetInstance()->EndDraw();

}

void TitleScene::Finalize() {



}
