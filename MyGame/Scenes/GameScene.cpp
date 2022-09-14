#include "GameScene.h"
#include"Input.h"
#include"SceneManager.h"
#include"Tutorial.h"
#include"Feed.h"
#include"Tuna.h"
#include"Egg.h"
#include"Player.h"
#include"imgui.h"
#include"Destroy.h"
#include"mHelper.h"
#include"SushiMove.h"
#include<fstream>
#include <algorithm>
#include"ResultScene.h"
#include"PlaceObj.h"
#include"Human.h"
#include"Samon.h"
#include"Collision.h"
#include <Base/Obj/3d/ModelManager.h>
#include <GameObj/LifeMgr.h>
#include <Base/Easing.h>
GameScene::GameScene(SceneManager* sceneManager)
	:BaseScene(sceneManager) {

}
void GameScene::Feed() {
	if (Change) {
		if (frame < 1.0f) {
			frame += 0.02f;
		} else {
			ScoreSave(ScoreMgr::GetIns()->GetScore());
			BaseScene* scene = new ResultScene(sceneManager_);//次のシーンのインスタンス生成
			SceneManager::GetInstance()->SetScene(SceneManager::RESULT);
			sceneManager_->SetnextScene(scene);//シーンのセット
		}
		alpha = Ease(In, Quad, frame, 0, 1);
		Effect->setcolor({ 1,1,1,alpha });
	}

}
/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize() {
	WaveSprite[WAVE1] = Sprite::Create(ImageManager::Wave1, { -300,0 });
	WaveSprite[WAVE2] = Sprite::Create(ImageManager::Wave2, { -300,0 });
	WaveSprite[WAVE3] = Sprite::Create(ImageManager::Wave3, { -300,0 });
	WaveSprite[WAVE4] = Sprite::Create(ImageManager::Wave4, { -300,0 });
	WaveSprite[WAVE5] = Sprite::Create(ImageManager::Wave6, { -300,0 });
	WaveSprite[WAVE6] = Sprite::Create(ImageManager::Wave6, { -300,0 });

	Sprite* BackGround_ = Sprite::Create(ImageManager::BG, { 0,0 });
	BackGround.reset(BackGround_);
	ScoreMgr::GetIns()->Init();
	ScoreMgr::GetIns()->ResetScore();
	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	sushinum.push_back(0);//最初はマグロ
	sushis.push_back(new Tuna());
	sushis[0]->Initialize();

	//寿司の動き
	smove2.push_back(new SushiMove());
	smove3.push_back(new SushiMove());
	//寿司の動き
	smove.push_back(new SushiMove());

	std::unique_ptr<Rail> newRail;
	for (int i = 0; i < 12; i++) {
		Rail* newRail_ = new Rail();
		newRail_->SetPosition(RailPos[i]);
		newRail_->SetRotation(RailRot[i]);
		newRail_->SetScale(RailSca[i]);
		newRail.reset(newRail_);
		Rails.push_back(std::move(newRail));
	}
	for (std::unique_ptr< Rail>& rail : Rails) {
		rail->Initialize();
	}
	pauseStart = new PauseStart();
	pauseStart->Init();

	LifeMgr::GetIns()->Init();
	LifeMgr::GetIns()->ResetLife();
	//スプライト生成
	Sprite* Effect_ = Sprite::Create(ImageManager::Black, { 0.0f,0.0f });
	Effect.reset(Effect_);
	Effect->setcolor({ 1,1,1,alpha });

	DustBox = std::make_unique<Object3d>();
	Dust = ModelManager::GetIns()->GetModel(ModelManager::Dust);
	DustBox->SetModel(Dust);
	DustBox->Initialize(CameraControl::GetInstance()->GetCamera());
	DustBox->SetPosition({ -4, -45, 7 - 3 });
	DustBox->SetScale({ 2.5f,2,2.5f });


	Gate = std::make_unique<Object3d>();
	GateModel = ModelManager::GetIns()->GetModel(ModelManager::Gate);
	Gate->SetModel(GateModel);
	Gate->Initialize(CameraControl::GetInstance()->GetCamera());
	Gate->SetPosition({ 35, -38, 14.5f });
	Gate->SetScale({ 5,5,5 });

	Gate2 = std::make_unique<Object3d>();
	Gate2->SetModel(GateModel);
	Gate2->Initialize(CameraControl::GetInstance()->GetCamera());
	Gate2->SetPosition({ 0.5f, -38, 40 });
	Gate2->SetScale({ 5,5,5 });
	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());
	//カメラをセット
	f_Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());
	//グラフィックパイプライン生成
	f_Object3d::CreateGraphicsPipeline();
	PlaceObj::GetInstance()->Init();

	Audio::GetInstance()->StopWave(0);
	Audio::GetInstance()->StopWave(2);

	Audio::GetInstance()->LoopWave(1, 0.3f);

}


/// <summary>
/// 更新処理
/// </summary>
void GameScene::Update() {
	///audio->PlayWave("Resources/Audio/AnyConv.com__井の中の蛙.wav", 1.3f); 
	if (first && pause) {
		pauseStart->Upda();
		if (pauseStart->GetPause()) {
			pause = false;
		}
		return;
	}
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());
	Wave1or2();
	Wave3();
	Wave4();
	WaveCont();
	ScoreMgr::GetIns()->Upda();
	LifeMgr::GetIns()->Upda();

	for (std::unique_ptr<Rail>& rail : Rails) {
		rail->Update();
	}
	PlaceObj::GetInstance()->Update(sushis);


	PlaceObj::GetInstance()->Update2(sushis2);

	PlaceObj::GetInstance()->Update3(sushis3);

	PlaceObj::GetInstance()->UpdateS();
	PlaceObj::GetInstance()->SetIconSpritePos();
	if (LifeMgr::GetIns()->GetLife() <= 0) {//押されたら
		Change = true;
	}
	DustBox->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	Gate->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	Gate2->Update({ 1,1,1,1 }, CameraControl::GetInstance()->GetCamera());
	if (!first) {
		first = true;
	}
}

/// <summary>
/// スプライト描画
/// </summary>
/// <param name="cmdList"></param>
void GameScene::SpriteDraw() {
	Sprite::PreDraw();
	BackGround->Draw();
	Sprite::PostDraw();
	DirectXCommon::GetInstance()->ClearDepthBuffer();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void GameScene::Draw() {
	//ポストエフェクトの描画
	DirectXCommon::GetInstance()->BeginDraw();//描画コマンドの上らへんに
	SpriteDraw();


	for (std::unique_ptr<Rail>& rail : Rails) {
		rail->Draw();
	}

	DustBox->Draw();

	PlaceObj::GetInstance()->Draw();

	PlaceObj::GetInstance()->Draw();

	Object3d::PreDraw();
	DustBox->Draw();
	Gate->Draw();
	Gate2->Draw();
	Object3d::PostDraw();
	for (int i = 0; i < sushis.size(); i++) {
		if (sushis[i] != nullptr) {
			sushis[i]->Draw();
		}
	}
	for (int i = 0; i < sushis2.size(); i++) {
		if (sushis2[i] != nullptr) {
			sushis2[i]->Draw();
		}
	}
	for (int i = 0; i < sushis3.size(); i++) {
		if (sushis3[i] != nullptr) {
			sushis3[i]->Draw();
		}
	}
	Sprite::PreDraw();
	for (int i = 0; i < _countof(WaveSprite); i++) {
		WaveSprite[i]->Draw();
	}
	ScoreMgr::GetIns()->Draw();
	LifeMgr::GetIns()->Draw();
	pauseStart->Draw();
	Sprite::PreDraw();
	Effect->Draw();
	Sprite::PostDraw();

	DirectXCommon::GetInstance()->EndDraw();
}
void GameScene::Finalize() {
	delete Gamesprite;
}

int GameScene::RetrandCount() {
	switch (fase) {
	case GameScene::WAVE1:
		return rand() % 340 + 300;
		break;
	case GameScene::WAVE2:
		return rand() % 260 + 220;
		break;
	case GameScene::WAVE3:
		return rand() % 340 + 300;
		break;
	case GameScene::WAVE4:
		return rand() % 380 + 340;
		return 0;
		break;
	case GameScene::WAVE5:
		return rand() % 340 + 300;
		return 0;
		break;
	case GameScene::CLEAR:
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

int GameScene::RetrandCount2() {
	switch (fase) {
	case GameScene::WAVE1:
		return rand() % 340 + 300;
		break;
	case GameScene::WAVE2:
		return rand() % 300 + 260;
		break;
	case GameScene::WAVE3:
		return rand() % 340 + 300;
		break;
	case GameScene::WAVE4:
		return rand() % 380 + 360;
		return 0;
		break;
	case GameScene::WAVE5:
		return rand() % 340 + 300;
		return 0;
		break;
	case GameScene::CLEAR:
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

int GameScene::RetrandCount3() {
	switch (fase) {
	case GameScene::WAVE1:
		return rand() % 240 + 200;
		break;
	case GameScene::WAVE2:
		return rand() % 400 + 380;
		break;
	case GameScene::WAVE3:
		return rand() % 400 + 380;
		break;
	case GameScene::WAVE4:
		return rand() % 340 + 300;
		return 0;
		break;
	case GameScene::WAVE5:
		return rand() % 340 + 300;
		return 0;
		break;
	case GameScene::CLEAR:
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

void GameScene::WaveCont() {
	switch (fase) {
	case GameScene::WAVE1:
		if (ETime[WAVE1] <= 1.0f) {
			ETime[WAVE1] += 0.01f;
		}
		WaveSprite[WAVE1]->SetPosition({ Easing::EaseOut(ETime[WAVE1], -300, 0),10 });
		if (SushiDeathCount > 5) {
			ETime[WAVE1] = 0;
			fase = WAVE2;
		}
		PlaceObj::GetInstance()->CenterBench_isUse(true);
		break;
	case GameScene::WAVE2:
		if (ETime[WAVE1] <= 1.0f) {
			ETime[WAVE1] += 0.01f;
		}
		WaveSprite[WAVE1]->SetPosition({ Easing::EaseOut(ETime[WAVE1], 0, -300),10 });

		if (ETime[WAVE2] <= 1.0f && ETime[WAVE1] >= 1.0f) {
			ETime[WAVE2] += 0.01f;
		}
		WaveSprite[WAVE2]->SetPosition({ Easing::EaseOut(ETime[WAVE2], -300, 0),10 });
		if (SushiDeathCount > 10) {
			ETime[WAVE2] = 0;
			sushinum2.push_back(0);//最初はマグロ
			sushis2.push_back(new Tuna());
			sushis2[0]->Initialize();
			//寿司の動き
			smove2.push_back(new SushiMove());

			fase = WAVE3;
		}
		break;

	case GameScene::WAVE3:
		PlaceObj::GetInstance()->RightBench_isUse(true);

		if (ETime[WAVE2] <= 1.0f) {
			ETime[WAVE2] += 0.01f;
		}
		WaveSprite[WAVE2]->SetPosition({ Easing::EaseOut(ETime[WAVE2], 0, -300),10 });

		if (ETime[WAVE3] <= 1.0f) {
			ETime[WAVE3] += 0.01f;
		}
		if (SushiDeathCount > 20) {
			ETime[WAVE3] = 0;
			sushinum3.push_back(0);//最初はマグロ
			sushis3.push_back(new Tuna());
			sushis3[0]->Initialize();
			//寿司の動き
			smove3.push_back(new SushiMove());

			fase = WAVE4;
		}
		WaveSprite[WAVE3]->SetPosition({ Easing::EaseOut(ETime[WAVE3], -300, 0),10 });

		break;
	case GameScene::WAVE4:

		if (ETime[WAVE3] <= 1.0f) {
			ETime[WAVE3] += 0.01f;
		}
		WaveSprite[WAVE3]->SetPosition({ Easing::EaseOut(ETime[WAVE3], 0, -300),10 });

		if (ETime[WAVE4] <= 1.0f) {
			ETime[WAVE4] += 0.01f;
		}
		if (SushiDeathCount > 25) {
			ETime[WAVE4] = 0;
			fase = WAVE5;
		}
		WaveSprite[WAVE4]->SetPosition({ Easing::EaseOut(ETime[WAVE4], -300, 0),10 });

		PlaceObj::GetInstance()->CenterBench_isUse(true);
		break;
	case GameScene::WAVE5:

		if (ETime[WAVE4] <= 1.0f) {
			ETime[WAVE4] += 0.01f;
		}
		WaveSprite[WAVE4]->SetPosition({ Easing::EaseOut(ETime[WAVE4], 0, -300),10 });

		if (ETime[WAVE5] <= 1.0f) {
			ETime[WAVE5] += 0.01f;
		}
		
		WaveSprite[WAVE5]->SetPosition({ Easing::EaseOut(ETime[WAVE5], -300, 0),10 });

		PlaceObj::GetInstance()->CenterBench_isUse(true);
		break;
	case GameScene::WAVE6:

		PlaceObj::GetInstance()->CenterBench_isUse(true);
		break;

	case GameScene::CLEAR:
		break;
	default:
		break;
	}
}

void GameScene::Wave1or2() {
	placeC++;

	if (placeC % RandPlaceCount == 0) {
		sushinum.push_back(rand() % 2);
		if (sushinum.back() == 0) {
			sushis.push_back(new Samon());
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
			if (sushis[i]->GetScale().x <= 0.0f) {
				SushiDeathCount++;
				Destroy(sushis[i]);
			}
		}
	}
}

void GameScene::Wave3() {
	if (fase == WAVE3) {
		placeC2++;
	}

	if ((placeC2 % RandPlaceCount2 == 0 && placeC2 != 0)) {
		sushinum2.push_back(rand() % 3);
		if (sushinum2.back() == 0) {
			sushis2.push_back(new Tuna());
			sushis2.back()->Initialize();
		} else if (sushinum2.back() == 1) {
			sushis2.push_back(new Egg());
			sushis2.back()->Initialize();
		}
		else if (sushinum2.back() == 2) {
			sushis2.push_back(new Samon());
			sushis2.back()->Initialize();
		}
		smove2.push_back(new SushiMove());
		RandPlaceCount2 = RetrandCount2();
		placeC2 = 0;
	}
	for (int i = 0; i < sushis2.size(); i++) {
		if (sushis2[i] != nullptr) {
			smove2[i]->Wave3move(sushis2[i]);
			sushis2[i]->Update();
			if (sushis2[i]->GetScale().x <= 0.0f) {
				SushiDeathCount++;
				Destroy(sushis2[i]);
			}
		}
	}
}


void GameScene::Wave4() {
	if (fase == WAVE4) {
		placeC3++;
	}

	if (placeC3 % RandPlaceCount3 == 0 && placeC3 != 0) {
		sushinum3.push_back(rand() % 2);
		if (sushinum3.back() == 0) {
			sushis3.push_back(new Tuna());
			sushis3.back()->Initialize();
		} else if (sushinum3.back() == 1) {
			sushis3.push_back(new Egg());
			sushis3.back()->Initialize();
		}
		else if (sushinum3.back() == 2) {
			sushis3.push_back(new Samon());
			sushis3.back()->Initialize();
		}
		smove3.push_back(new SushiMove());
		RandPlaceCount3 = RetrandCount3();
		placeC3 = 0;
	}
	for (int i = 0; i < sushis3.size(); i++) {
		if (sushis3[i] != nullptr) {
			smove3[i]->Wave4move(sushis3[i]);
			sushis3[i]->Update();
			if (sushis3[i]->GetScale().x <= 0.0f) {
				SushiDeathCount++;
				Destroy(sushis3[i]);
			}
		}
	}
}
void GameScene::LoadRanking() {
	std::ifstream file;
	file.open("Resources/csv/Ranking.csv");
	assert(file.is_open());

	csvRanking << file.rdbuf();

	file.close();
}

void GameScene::PushBackRank() {
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

void GameScene::ScoreSave(float Score) {
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