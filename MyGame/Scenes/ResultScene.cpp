#include"ResultScene.h"
#include<fstream>
#include <algorithm>
#include <Base/Obj/3d/Object3d.h>
#include <Base/Camera/CameraControl.h>

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
			break;
		}
	}

}

void ResultScene::ScoreSave(float Score) {
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
	file.close();

}

void ResultScene::Initialize() {
	ScoreSave(50);
	const int w = 32;
	const int h = 64;
	const int l = 10;
	const float onePos = WinApp::window_width - 208.0f;
	Sprite::LoadTexture(10, L"Resources/2d/Num.png");
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 10; j++) {
				num[k][i][j] = Sprite::Create(10,{0.0f,0.0f});
				int number_index_y = j / l;
				int number_index_x = j % l;
				num[k][i][j]->SetTextureRect(
					{ static_cast<float>(number_index_x) * w, static_cast<float>(number_index_y) * h },
					{ static_cast<float>(w), static_cast<float>(h) });
				num[k][i][j]->SetSize({ w,h });
				num[k][i][j]->SetAnchorPoint({ 0,0 });
				num[k][i][j]->SetSize({ w*2,h*2 });
				num[k][i][j]->SetPosition({ (float)WinApp::window_width - 93.0f - 55.0f * i ,128.0f* k});
			}
		}
	}

	int a = 0;
	a++;
	CameraControl::GetInstance()->Initialize(CameraControl::GetInstance()->GetCamera());
	Object3d::SetCamera(CameraControl::GetInstance()->GetCamera());

}

void ResultScene::Update() {
	CameraControl::GetInstance()->Update(CameraControl::GetInstance()->GetCamera());

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
}

void ResultScene::Draw() {
	//ポストエフェクトの描画
	DirectXCommon::GetInstance()->BeginDraw();//描画コマンドの上らへんに

	Sprite::PreDraw();
	for (int i = 0; i < First.size() && i < 5; i++) {
		num[0][i][(int)First[i]]->Draw();
	}
	for (int i = 0; i < Second.size() && i < 5; i++) {
		num[1][i][(int)Second[i]]->Draw();
	}
	for (int i = 0; i < Third.size() && i < 5; i++) {
		num[2][i][(int)Third[i]]->Draw();
	}
	Sprite::PostDraw();
	DirectXCommon::GetInstance()->EndDraw();

}

void ResultScene::SpriteDraw() {
}

void ResultScene::Finalize() {
}
