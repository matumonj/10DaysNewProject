#include "TitleScene.h"
#include"Input.h"
#include"SceneManager.h"
#include "GameScene.h"
#include"Tuna.h"
#include "Egg.h"
#include "Samon.h"
#include <Base/Easing.h>

TitleScene::TitleScene(SceneManager* sceneManager) 
	:BaseScene(sceneManager) {
}

void TitleScene::Initialize() {
	Sprite* BackGround_ = Sprite::Create(ImageManager::Title, { 0,0 });
	BackGround.reset(BackGround_);

	sushis.push_back(new Tuna());
	sushis.push_back(new Egg());
	sushis.push_back(new Samon());
	sushis.push_back(new Tuna());
	sushis.push_back(new Egg());
	sushis.push_back(new Samon());
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->SetPos({ i * 5.0f,-20.0f,0 });
			sushis[i]->Initialize();
	}

	//�X�v���C�g����
	Sprite* Effect_ = Sprite::Create(ImageManager::Black, { 0.0f,0.0f });
	Effect.reset(Effect_);
	Effect->setcolor({ 1,1,1,alpha });


	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());
}

void TitleScene::Update() {
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->TitleUpda();

	}
	if (Input::GetInstance()->TriggerKey(DIK_SPACE) || Input::GetInstance()->PushMouseLeft()) {//�����ꂽ��
		Change = true;
	}
	Feed();

}

void TitleScene::Draw() {
	DirectXCommon::GetInstance()->BeginDraw();//�`��R�}���h�̏��ւ��
	Sprite::PreDraw();
	BackGround->Draw();
	Sprite::PostDraw();
	DirectXCommon::GetInstance()->ClearDepthBuffer();
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->Draw();
	}
	Sprite::PreDraw();
	Effect->Draw();
	Sprite::PostDraw();

	DirectXCommon::GetInstance()->EndDraw();

}

void TitleScene::Finalize() {



}
void TitleScene::Feed() {
	if (Change) {
		if (frame < 1.6f) {
			frame += 0.02f;
		} else {
			BaseScene* scene = new GameScene(sceneManager_);//���̃V�[���̃C���X�^���X����
			SceneManager::GetInstance()->SetScene(SceneManager::PLAY);
			sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
		}
		alpha = Ease(In, Quad, frame, 0, 1);
		Effect->setcolor({ 1,1,1,alpha });
	}

}
