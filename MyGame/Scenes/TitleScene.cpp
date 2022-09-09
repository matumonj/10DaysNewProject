#include "TitleScene.h"
#include"Input.h"
#include"SceneManager.h"
#include"Tutorial.h"
#include"Feed.h"
#include"Tuna.h"
#include"Egg.h"
#include"CameraControl.h"
#include"Player.h"
#include"imgui.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	sushis.push_back(new Tuna());
	
	//for (int i = 0; i < sushis.size(); i++) {
		sushis[0]->Initialize();
		activs.push_back(true);
		sushinum.push_back(0);
	//}
	std::unique_ptr<Bench> newBench;
	Bench* newBench_ = new Bench();
	newBench.reset(newBench_);
	Benchs.push_back(std::move(newBench));
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Initialize();
	}
	Player::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{ 
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	

	for (int i = 0; i < activs.size(); i++) {
		if (activs[i]) {
			
		}
	}
	placeC++;
	
	if (placeC%RandPlaceCount==0) {
		activs.push_back(true);
		sushinum.push_back(rand()%2);
		if (sushinum.back() == 0) {
			sushis.push_back(new Tuna());
			sushis.back()->Initialize();
		}
		else if (sushinum.back() == 1) {
			sushis.push_back(new Egg());
			sushis.back()->Initialize();
		}
		RandPlaceCount = rand() % 240 + 120;
		placeC = 0;
	}
		for (int i = 0; i < sushis.size(); i++) {
			if (sushis[i] != nullptr) {
				
				sushis[i]->Update();
			}
			
		}
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update();
	}
	//Player::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());

	if (Input::GetInstance()->TriggerButton(Input::Button_B)) {//押されたら
		BaseScene* scene = new Tutorial(sceneManager_);//次のシーンのインスタンス生成
		SceneManager::GetInstance()->SetScene(SceneManager::TUTORIAL);
		sceneManager_->SetnextScene(scene);//シーンのセット
	}
}

/// <summary>
/// スプライト描画
/// </summary>
/// <param name="cmdList"></param>
void TitleScene::SpriteDraw()
{
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
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Draw();
	}
	for (int i = 0; i < sushis.size(); i++) {
			sushis[i]->Draw();
		
	}
	//やろうとしたがここでエラーを吐く
	ImGui::Begin("siz");
	ImGui::Text("size%d", activs.size());
	ImGui::End();
	//Player::GetInstance()->Draw();
	DirectXCommon::GetInstance()->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}