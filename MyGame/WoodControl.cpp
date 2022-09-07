#include "WoodControl.h"
#include"SceneManager.h"
#include"PlayerControl.h"
#include"mHelper.h"
WoodControl* WoodControl::GetInstance()
{
	static WoodControl instance;

	return &instance;
}

WoodControl::~WoodControl()
{
}

void WoodControl::Load(DebugCamera* camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		file.open("Param_CSV/wood.csv");

		popcom << file.rdbuf();

		file.close();

		while (std::getline(popcom, line)) {
			std::istringstream line_stream(line);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Wood_Quantity") == 0) {
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
		woods.resize(Quantity);

		Load_WoodPosition.resize(Quantity);

		for (int i = 0; i < Quantity; i++) {

			woods[i] = std::make_unique<Wood>();

			woods[i]->Initialize(camera);
			woods[i]->SetPosition(pos[i]);
		}
	}
		if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
			Tutorialwoods.resize(3);
			Tutorialwoods[0] = std::make_unique<Wood>();
			Tutorialwoods[1] = std::make_unique<Wood>();
			Tutorialwoods[2] = std::make_unique<Wood>();
			for (int i = 0; i < 3; i++) {
				Tutorialwoods[i]->Initialize(camera);
			}
			Tutorialwoods[0]->SetPosition({92,-10,-689});
			Tutorialwoods[1]->SetPosition({ 70,-10,-700 });
			Tutorialwoods[2]->SetPosition({ 110,-10,-720 });
		}
	UpdateRange = 200;
}

void WoodControl::Initialize(DebugCamera* camera)
{

}

void WoodControl::Update(DebugCamera* camera)
{
	Player_OldPos= PlayerControl::GetInstance()->GetPlayer()->GetPosition();
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		for (int i = 0; i < Quantity; i++) {
			//	if (woods[i] != nullptr) {
			woods[i]->SetColor({ 0,1,0,1 });
			//if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(),woods[i]->GetPosition()) <UpdateRange) {
			woods[i]->Update(camera);
			//}
		//}
		}
		for (int i = 0; i < Quantity; i++) {
			if (woods[i]->CollideWood() == true) {
				PlayerControl::GetInstance()->GetPlayer()->SetPosition(Player_OldPos);
				PlayerControl::GetInstance()->GetPlayer()->SetGround(true);
				break;
			}
		}
	}

	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		for (int i = 0; i < 3; i++) {
			//	if (woods[i] != nullptr) {
			Tutorialwoods[i]->SetColor({ 0,1,0,1 });
			//if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(),woods[i]->GetPosition()) <UpdateRange) {
			Tutorialwoods[i]->Update(camera);
			//}
		//}
		}
		for (int i = 0; i < 3; i++) {
			if (Tutorialwoods[i]->CollideWood() == true) {
				PlayerControl::GetInstance()->GetPlayer()->SetPosition(Player_OldPos);
				PlayerControl::GetInstance()->GetPlayer()->SetGround(true);
				break;
			}
		}
	}
}

void WoodControl::Draw()
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		for (int i = 0; i < Quantity; i++) {
			if (woods[i] != nullptr) {
				//if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(), woods[i]->GetPosition()) <UpdateRange) {
				woods[i]->Draw();
				//}
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		for (int i = 0; i <3; i++) {
			if (Tutorialwoods[i] != nullptr) {
				//if (Collision::GetLength(PlayerControl::GetInstance()->GetPlayer()->GetPosition(), woods[i]->GetPosition()) <UpdateRange) {
				Tutorialwoods[i]->Draw();
				//}
			}
		}
	}
}

void WoodControl::ImGuiDraw()
{

}


void WoodControl::SetColor(XMFLOAT4 color)
{
	
}