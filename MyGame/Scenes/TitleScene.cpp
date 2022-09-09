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
#include"Destroy.h"
#include"mHelper.h"
TitleScene::TitleScene(SceneManager* sceneManager)
	:BaseScene(sceneManager)
{

}
/// <summary>
/// 初期化
/// </summary>
void TitleScene::Initialize()
{
	Sprite::LoadTexture(2, L"Resources/2d/Wave/wave1.png");
	Sprite::LoadTexture(3, L"Resources/2d/Wave/wave2.png");
	Sprite::LoadTexture(4, L"Resources/2d/Wave/wave3.png");
	Sprite::LoadTexture(5, L"Resources/2d/Wave/wave4.png");

	WaveSprite[0] = Sprite::Create(2, { -300,0 });
	WaveSprite[1] = Sprite::Create(3, { -300,0 });
	WaveSprite[2] = Sprite::Create(4, { -300,0 });
	WaveSprite[3] = Sprite::Create(5, { -300,0 });
	for (int i = 0; i < _countof(WaveSprite); i++) {
		WaveSprite[i]->SetSize({ 400,400 });
	}
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
	
	placeC++;
	
	if (placeC%RandPlaceCount==0) {
		sushinum.push_back(rand()%2);
		if (sushinum.back() == 0) {
			sushis.push_back(new Tuna());
			sushis.back()->Initialize();
		}
		else if (sushinum.back() == 1) {
			sushis.push_back(new Egg());
			sushis.back()->Initialize();
		}
		RandPlaceCount = RetrandCount();
		placeC = 0;
	}
		for (int i = 0; i < sushis.size(); i++) {
			if (sushis[i] != nullptr) {
				sushis[i]->Update();

				if (sushis[i]->GetState() == sushis[i]->DEAD) {
					SushiDeathCount++;
					Destroy(sushis[i]);
				}
			}
			
		}
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update();
	}
	//Player::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	WaveCont();
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
		if (sushis[i] != nullptr) {
			sushis[i]->Draw();
		}
		
	}
	Sprite::PreDraw();
	for (int i = 0; i < _countof(WaveSprite); i++) {
		WaveSprite[i]->Draw();
	}
	Sprite::PostDraw();
	//やろうとしたがここでエラーを吐く
	ImGui::Begin("siz");
	ImGui::Text("size%d", SushiDeathCount);
	ImGui::End();
	//Player::GetInstance()->Draw();
	DirectXCommon::GetInstance()->EndDraw();

}
void TitleScene::Finalize()
{
	//delete postEffect;
	delete titlesprite;
}

int TitleScene::RetrandCount()
{
	switch (fase)
	{
	case TitleScene::WAVE1:
		
		return rand() % 240 + 200;
		break;
	case TitleScene::WAVE2:
		
		return rand() % 240 + 120;
		break;
	case TitleScene::WAVE3:
		
		break;
	case TitleScene::WAVE4:
		break;
	case TitleScene::CLEAR:
		break;
	default:
		break;
	}
}

void TitleScene::WaveCont()
{
	switch (fase)
	{
	case TitleScene::WAVE1:
		if (ETime[WAVE1] <= 1.0f) {
			ETime[WAVE1] += 0.01f;
		}
		WaveSprite[WAVE1]->SetPosition({ Easing::EaseOut(ETime[WAVE1], -300, 100),100 });
		if (SushiDeathCount > 6) {
			ETime[WAVE1] = 0;
			fase = WAVE2;
		}
		
		break;
	case TitleScene::WAVE2:
		if (ETime[WAVE1] <= 1.0f) {
			ETime[WAVE1] += 0.01f;
		}
		WaveSprite[WAVE1]->SetPosition({ Easing::EaseOut(ETime[WAVE1], 100, -300),100 });

		if (ETime[WAVE2] <= 1.0f&& ETime[WAVE1] >= 1.0f) {
			ETime[WAVE2] += 0.01f;
		}
		WaveSprite[WAVE2]->SetPosition({ Easing::EaseOut(ETime[WAVE2], -300, 100),100 });

		break;
	case TitleScene::WAVE3:
		if (ETime[WAVE3] <= 1.0f) {
			ETime[WAVE3] += 0.01f;
		}
		break;
	case TitleScene::WAVE4:
		break;
	case TitleScene::CLEAR:
		break;
	default:
		break;
	}
}