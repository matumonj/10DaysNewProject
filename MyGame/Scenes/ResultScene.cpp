#include"ResultScene.h"
#include<fstream>
#include <algorithm>

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
		//��͂��₷������
		std::istringstream line_stream(line);

		std::string word;
		//���p�X�y�[�X��؂�ōs�̐擪��������擾
		getline(line_stream, word, ',');
		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//��΂�
			continue;
		}
		//�e�R�}���h
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
	std::sort(Rank.begin(), Rank.end(), std::greater<float>());//�~���\�[�g	
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
	ScoreSave(55);
	int a = 0;
	a++;
}

void ResultScene::Update() {
}

void ResultScene::Draw() {
}

void ResultScene::SpriteDraw() {
}

void ResultScene::Finalize() {
}
