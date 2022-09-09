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
<<<<<<< HEAD
#include"SushiMove.h"
=======
#include<fstream>
#include <algorithm>
#include"ResultScene.h"


>>>>>>> 7462e226febaf65a0008333e59e51dc11af6168f
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
	sushinum.push_back(0);//最初はマグロ
	sushis.push_back(new Tuna());
	sushis[0]->Initialize();
	//寿司の動き
	smove.push_back(new SushiMove());
	sushinum2.push_back(0);//最初はマグロ

	sushis2.push_back(new Tuna());
	sushis2[0]->Initialize();
	//寿司の動き
	smove2.push_back(new SushiMove());
	std::unique_ptr<Bench> newBench;
	Bench* newBench_ = new Bench();
	newBench.reset(newBench_);
	Benchs.push_back(std::move(newBench));
	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Initialize();
	}
	//Player::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{ 
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	Wave1or2();
	Wave3();

	for (std::unique_ptr<Bench>& bench : Benchs) {
		bench->Update();
	}
	//Player::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	WaveCont();
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {//押されたら
		ScoreSave(score);
		BaseScene* scene = new ResultScene(sceneManager_);//次のシーンのインスタンス生成
		SceneManager::GetInstance()->SetScene(SceneManager::RESULT);
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
	ImGui::Text("size%d", sushis.size());
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
		
		return rand() % 180 + 140;
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
		if (SushiDeathCount > 1) {
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

<<<<<<< HEAD
void TitleScene::Wave1or2()
{
	placeC++;

	if (placeC % RandPlaceCount == 0) {
		sushinum.push_back(rand() % 2);
		if (sushinum.back() == 0) {
			sushis.push_back(new Tuna());
			sushis.back()->Initialize();
		} else if (sushinum.back() == 1) {
			sushis.push_back(new Egg());
			sushis.back()->Initialize();
		}
		smove.push_back(new SushiMove());
		RandPlaceCount = RetrandCount();
		placeC = 0;
	}
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
			smove[i]->Wave1or2move(sushis[i]);
			sushis[i]->Update();

			if (sushis[i]->GetDead()) {
				SushiDeathCount++;
				Destroy(sushis[i]);
			}
		}
	}
}

void TitleScene::Wave3()
{
	if (fase == WAVE2) {
		placeC2++;
	}

	if (placeC2 % RandPlaceCount2 == 0&&placeC2!=0) {
		sushinum2.push_back(rand() % 2);
		if (sushinum2.back() == 0) {
			sushis2.push_back(new Tuna());
			sushis2.back()->Initialize();
		} else if (sushinum2.back() == 1) {
			sushis2.push_back(new Egg());
			sushis2.back()->Initialize();
		}
		smove2.push_back(new SushiMove());
		RandPlaceCount2 = RetrandCount();
		placeC2 = 0;
	}
	for (int i = 0; i < sushis2.size(); i++) {
		if (sushis2[i] != nullptr) {
			smove2[i]->Wave3move(sushis2[i]);
			sushis2[i]->Update();

			if (sushis2[i]->GetDead()) {
				SushiDeathCount++;
				Destroy(sushis2[i]);
			}
		}
	}
}
=======

void TitleScene::LoadRanking() {
	std::ifstream file;
	file.open("Resources/csv/Ranking.csv");
	assert(file.is_open());

	csvRanking << file.rdbuf();

	file.close();
}

void TitleScene::PushBackRank() {
	LoadRanking();
	std::string line;

	while (getline(csvRanking, line)) {
		//解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//半角スペース区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//飛ばす
			continue;
		}
		//各コマンド
		if (word.find("FIRST") == 0) {
			getline(line_stream, word, ',');
			float F = (float)std::atof(word.c_str());
			Rank.push_back(F);
		} else if (word.find("SECOND") == 0) {
			getline(line_stream, word, ',');
			float S = (float)std::atof(word.c_str());
			Rank.push_back(S);
		} else if (word.find("THIRD") == 0) {
			getline(line_stream, word, ',');
			float T = (float)std::atof(word.c_str());
			Rank.push_back(T);
		} else if (word.find("NOW") == 0) {
			getline(line_stream, word, ',');
			float N = (float)std::atof(word.c_str());
			Rank.push_back(N);
			break;
		}

	}

}

void TitleScene::ScoreSave(float Score) {
	PushBackRank();
	Rank.push_back(Score);
	std::sort(Rank.begin(), Rank.end(), std::greater<float>());//降順ソート	
	std::ofstream file("Resources/csv/Ranking.csv");
	file << "FIRST" << ',';
	file << Rank[0] << ',';
	file << std::endl;
	file << "SECOND" << ',';
	file << Rank[1] << ',';
	file << std::endl;
	file << "THIRD" << ',';
	file << Rank[2] << ',';
	file << std::endl;
	file << "NOW" << ',';
	file << Score << ',';
	file << std::endl;
	file.close();

}
>>>>>>> 7462e226febaf65a0008333e59e51dc11af6168f
