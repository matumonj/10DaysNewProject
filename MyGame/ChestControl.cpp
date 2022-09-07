#include "ChestControl.h"
#include"SceneManager.h"
#include"Destroy.h"
#include"PlayerControl.h"
ChestControl* ChestControl::GetInstance()
{
	static ChestControl instance;

	return&instance;
}
void ChestControl::Load(DebugCamera* camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
	//ChestMaxも追加
	file.open("Param_CSV/Chest.csv");

	popcom << file.rdbuf();

	file.close();

	while (std::getline(popcom, line)) {
		std::istringstream line_stream(line);
		std::string word;
		std::getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}
		if (word.find("Chest_Quantity") == 0) {
			std::getline(line_stream, word, ',');
			int quantity = (int)std::atof(word.c_str());
			Quantity = quantity;
			break;
		}
	}
	Num.resize(Quantity);
	pos.resize(Quantity);
	for (int i = 0; i < Quantity; i++) {
		while (std::getline(popcom, line)) {
			std::istringstream line_stream(line);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("POP") == 0) {
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());

				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				pos[i] = { x,y,z };
				break;
			}
		}
	}
	chests.resize(Quantity);

	Load_ChestPosition.resize(Quantity);

	for (int i = 0; i < Quantity; i++) {

		chests[i] = std::make_unique<Chest>();

		chests[i]->Initialize(camera);
		chests[i]->SetPosition(pos[i]);
	}
}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
			Tutorial_chest.resize(1);
		Tutorial_chest[0] = std::make_unique<Chest>();
		Tutorial_chest[0]->Initialize(camera);
		Tutorial_chest[0]->SetPosition({ 115,-24,-576 });
		Tutorial_chest[0]->SetRotation({ 0,90,0 });
		//Tutorial_chest[0]->SetScale({ 8.39,10,4 });
	}
	UpdateRange = 200;
}

void ChestControl::Initialize(DebugCamera* camera)
{

}

void ChestControl::Update(DebugCamera* camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		for (int i = 0; i < Quantity; i++) {
			if (chests[i] != nullptr) {
				chests[i]->SetColor({ 1,1,1,1 });
				//if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(), chests[i]->GetPosition()) < UpdateRange) {
				chests[i]->Update(camera);
				//}
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (Tutorial_chest[0] != nullptr) {
			Tutorial_chest[0]->SetColor({ 1,1,1,1 });
			Tutorial_chest[0]->Update(camera);
			//}
			if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(), Tutorial_chest[0]->GetPosition()) < 10) {
				GetTutorialChestJudg = true;;//チュートリアル用
				GetChestAction();
				Destroy_unique(Tutorial_chest[0]);
				
			}
			
		}
	}
	
}

void ChestControl::Draw()
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
	for (int i = 0; i < Quantity; i++) {
		if (chests[i] != nullptr) {
		//	if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(), chests[i]->GetPosition()) < UpdateRange) {
				chests[i]->Draw();
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (Tutorial_chest[0] != nullptr) {
			Tutorial_chest[0] ->Draw();
		}
	}
}


void ChestControl::GetChestAction()
{
	bool GetMaxChests = GetChestCount == Quantity+1;
	GetChestCount++;
	ChestDestroy();

	
	if (GetMaxChests) {
		//BOSS登場シーンへに切り替え
	}
}

void ChestControl::ChestDestroy()
{
	//破棄処理　終わったらnullptr
}
