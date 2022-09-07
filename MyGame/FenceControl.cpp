#include "FenceControl.h"
#include "EnemyControl.h"
#include"SceneManager.h"
#include"TutorialSprite.h"
#include"PlayerControl.h"
#include"Enemy.h"
FenceControl* FenceControl::GetInstance()
{
	static FenceControl instance;
	return &instance;
}
void FenceControl::Load(DebugCamera* camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		file.open("Param_CSV/fence.csv");

		popcom << file.rdbuf();

		file.close();

		while (std::getline(popcom, line)) {
			std::istringstream line_stream(line);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Fence_Quantity") == 0) {
				std::getline(line_stream, word, ',');
				int quantity = (int)std::atof(word.c_str());
				Quantity = quantity;
				break;
			}
		}
		Num.resize(Quantity);
		pos.resize(Quantity);
		rot.resize(Quantity);
		scl.resize(Quantity);
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
					//break;
				}
				if (word.find("ROTATION") == 0) {
					std::getline(line_stream, word, ',');
					float x = (float)std::atof(word.c_str());

					std::getline(line_stream, word, ',');
					float y = (float)std::atof(word.c_str());

					std::getline(line_stream, word, ',');
					float z = (float)std::atof(word.c_str());

					rot[i] = { x,y,z };
					//break;
				}
				if (word.find("SCALE") == 0) {
					std::getline(line_stream, word, ',');
					float x = (float)std::atof(word.c_str());

					std::getline(line_stream, word, ',');
					float y = (float)std::atof(word.c_str());

					std::getline(line_stream, word, ',');
					float z = (float)std::atof(word.c_str());

					scl[i] = { x,y,z };
					break;
				}
			}
		}
		fences.resize(Quantity);

		Load_FencePosition.resize(Quantity);

		for (int i = 0; i < Quantity; i++) {
			fences[i] = std::make_unique<AreaFence>();
			fences[i]->Initialize(camera);
			fences[i]->SetPosition(pos[i]);
			fences[i]->SetRotation(rot[i]);
			fences[i]->SetScale(scl[i]);
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		Tutorialfence.resize(1);
		Tutorialfence[0]= std::make_unique<AreaFence>();
		Tutorialfence[0]->Initialize(camera);
		Tutorialfence[0]->SetPosition({110,-40,-596});
		Tutorialfence[0]->SetRotation({0,0,0});
		Tutorialfence[0]->SetScale({8.39,10,4});
	}
}

void FenceControl::Initialize(DebugCamera* camera)
{

}

void FenceControl::Update(DebugCamera* camera)
{
	if (EnemyControl::GetInstance()->GetTutorialEnemyindex()[0] != nullptr) {
		TutorialFenceOpen = EnemyControl::GetInstance()->GetTutorialEnemyindex()[0]->GetHP() < 0;
		//if (fences[0].get() == nullptr)return;
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		Player_OldPos = PlayerControl::GetInstance()->GetPlayer()->GetPosition();
		for (int i = 0; i < Quantity; i++) {
			if (fences[i] != nullptr) {
				fences[i]->Update(camera);
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (Tutorialfence[0] != nullptr) {
			Tutorialfence[0]->Update(camera);
			Tutorialfence[0]->SetColor({ 1,0,0,1 });
		}
		Tutorialfence[0]->FenceOpenCondition(TutorialFenceOpen);
		
	}
}

void FenceControl::Draw()
{
	//if (fences[0].get() == nullptr)return;
	//if (fences[0].get() != nullptr) {
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {

		for (int i = 0; i < Quantity; i++) {
			if (fences[i] != nullptr) {
				fences[i]->Draw();
			}
		}
		}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (Tutorialfence[0] != nullptr) {
			Tutorialfence[0]->Draw();
		}
	}
	//}
}

void FenceControl::ImGuiDraw()
{

}

void FenceControl::SetColor(XMFLOAT4 color)
{
	
}