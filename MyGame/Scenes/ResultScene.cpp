#include"ResultScene.h"
#include<fstream>
#include <algorithm>
#include <Base/Obj/3d/Object3d.h>
#include <Base/Camera/CameraControl.h>
#include"SceneManager.h"
#include"TitleScene.h"
ResultScene::ResultScene(SceneManager* sceneManager)
	:BaseScene(sceneManager) {
}

void ResultScene::LoadRanking() {
	std::ifstream file;
	file.open("Resources/csv/Ranking.csv");
	assert(file.is_open());

	csvRanking << file.rdbuf();

	file.close();
}

void ResultScene::PushBackRank() {
	LoadRanking();
	std::string line;
	Rank.clear();
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

void ResultScene::ResultInit() {
	First.clear();
	for (int tmp = (int)Rank[0]; tmp > 0;) {
		First.push_back(tmp % 10);
		tmp /= 10;
	}
	Second.clear();
	for (int tmp = (int)Rank[1]; tmp > 0;) {
		Second.push_back(tmp % 10);
		tmp /= 10;
	}
	Third.clear();
	for (int tmp = (int)Rank[2]; tmp > 0;) {
		Third.push_back(tmp % 10);
		tmp /= 10;
	}
	Now.clear();
	for (int tmp = (int)Rank[3]; tmp > 0;) {
		Now.push_back(tmp % 10);
		tmp /= 10;
	}
}

void ResultScene::Initialize() {
	PushBackRank();
	ResultInit();
	const int w = 32;
	const int h = 64;
	const int l = 10;

	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				num[k][i][j] = Sprite::Create(ImageManager::Num, { 0.0f,0.0f });
				int number_index_y = j / l;
				int number_index_x = j % l;
				num[k][i][j]->SetTextureRect(
					{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
					{ static_cast<float>(w), static_cast<float>(h) });
				num[k][i][j]->SetSize({ w,h });
				num[k][i][j]->SetAnchorPoint({ 0,0.5f });
				num[k][i][j]->SetSize({ w * 2,h * 2 });
				num[k][i][j]->setcolor({0.0f,0.0f,0.0f,1.0f});
				num[k][i][j]->SetPosition({ (float)(WinApp::window_width / 2.0f) - (70.0f * i) ,(128.0f * k) + 200.0f });
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			num[0][i][j]->SetPosition({ EaseX[0] - (70.0f * i) , 200.0f });
			num[1][i][j]->SetPosition({ EaseX[1] - (70.0f * i) , 360.0f });
			num[2][i][j]->SetPosition({ EaseX[2] - (70.0f * i) , 520.0f });
			num[3][i][j]->SetPosition({ EaseX[3] - (70.0f * i) , 40.0f });
		}
	}
	Sprite* BackGround_ = Sprite::Create(ImageManager::Result, { 0,0 });
	BackGround.reset(BackGround_);
	Audio::GetInstance()->StopWave(0);
	Audio::GetInstance()->StopWave(1);
	Audio::GetInstance()->LoopWave(2, 0.3f);

	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());
}

void ResultScene::Update() {
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());

	if (ETime[0] <= 1.0f) {
		ETime[0] += 0.02f;
	}
	if (ETime[0] >= 0.3f) {
		if (ETime[1] <= 1.0f) {
			ETime[1] += 0.02f;
		}
	}
	if (ETime[1] >= 0.3f) {
		if (ETime[2] <= 1.0f) {
			ETime[2] += 0.02f;
		}
	}

	if (Rank[3]==Rank[0]) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				num[0][i][j]->setcolor({1,0,0,1});
				num[3][i][j]->setcolor({1,0,0,1});
			}
		}
	}
	if (Rank[3] == Rank[1]) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				num[1][i][j]->setcolor({ 1,0,0,1 });
				num[3][i][j]->setcolor({ 1,0,0,1 });
			}
		}
	}
	if (Rank[3] == Rank[2]) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				num[2][i][j]->setcolor({ 1,0,0,1 });
				num[3][i][j]->setcolor({ 1,0,0,1 });
			}
		}
	}

	EaseX[0] = Easing::EaseOut(ETime[0], 1600, 780);
	EaseX[1] = Easing::EaseOut(ETime[1], 1600, 780);
	EaseX[2] = Easing::EaseOut(ETime[2], 1600, 780);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			num[0][i][j]->SetPosition({ EaseX[0] - (70.0f * i) , 200.0f });
			num[1][i][j]->SetPosition({ EaseX[1] - (70.0f * i) , 360.0f });
			num[2][i][j]->SetPosition({ EaseX[2] - (70.0f * i) , 520.0f });
		}
	}

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {//押されたら
		Audio::GetInstance()->PlayWave("Resources/Audio/bgm_wav/start.wav", 0.5f);
		BaseScene* scene = new TitleScene(sceneManager_);//次のシーンのインスタンス生成
		SceneManager::GetInstance()->SetScene(SceneManager::TITLE);
		sceneManager_->SetnextScene(scene);//シーンのセット
	}



}

void ResultScene::Draw() {
	//ポストエフェクトの描画
	DirectXCommon::GetInstance()->BeginDraw();//描画コマンドの上らへんに

	Sprite::PreDraw();
	BackGround->Draw();
	if (Rank[0] == 0) {
		num[0][0][0]->Draw();
	} else {
		for (int i = 0; i < First.size() && i < 5; i++) {
			num[0][i][(int)First[i]]->Draw();
		}
	}
	if (Rank[1] == 0) {
		num[1][0][0]->Draw();
	} else {
		for (int i = 0; i < Second.size() && i < 5; i++) {
			num[1][i][(int)Second[i]]->Draw();
		}
	}
	if (Rank[2] == 0) {
		num[2][0][0]->Draw();
	} else {
		for (int i = 0; i < Third.size() && i < 5; i++) {
			num[2][i][(int)Third[i]]->Draw();
		}
	}
	if (Rank[3] == 0) {
		num[3][0][0]->Draw();
	} else {
		for (int i = 0; i < Now.size() && i < 5; i++) {
			num[3][i][(int)Now[i]]->Draw();
		}
	}
	Sprite::PostDraw();
	DirectXCommon::GetInstance()->EndDraw();

}

void ResultScene::Finalize() {
}
