#include "TitleScene.h"
#include"Input.h"
#include"SceneManager.h"
#include"Tutorial.h"
#include"Feed.h"
#include"Tuna.h"
#include"Egg.h"
#include"CameraControl.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// ������
/// </summary>
void TitleScene::Initialize()
{
	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	sushis.push_back(new Tuna());
	for (int i = 0; i < sushis.size(); i++) {
		sushis[i]->Initialize();
	}
	std::unique_ptr<Bench> newBench;
	Bench* newBench_ = new Bench();
	newBench.reset(newBench_);
	Benchs.push_back(std::move(newBench));
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Initialize();
	}

	// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

}

/// <summary>
/// �X�V����
/// </summary>
void TitleScene::Update()
{ 
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	for (int i = 0; i < sushis.size(); i++) {
		sushis[i]->Update();
	}
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update();
	}

	if (Input::GetInstance()->TriggerButton(Input::Button_B)) {//�����ꂽ��
		BaseScene* scene = new Tutorial(sceneManager_);//���̃V�[���̃C���X�^���X����
		SceneManager::GetInstance()->SetScene(SceneManager::TUTORIAL);
		sceneManager_->SetnextScene(scene);//�V�[���̃Z�b�g
	}
}

/// <summary>
/// �X�v���C�g�`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::Draw()
{
	//�|�X�g�G�t�F�N�g�̕`��
	DirectXCommon::GetInstance()->BeginDraw();//�`��R�}���h�̏��ւ��
	SpriteDraw();
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Draw();
	}
	for (int i = 0; i < sushis.size(); i++) {
		sushis[i]->Draw();
	}
	DirectXCommon::GetInstance()->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}