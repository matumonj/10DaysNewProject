#include"EnemyControl.h"
#include"MobEnemy.h"
#include"BossEnemy.h"

#include"TutorialSprite.h"
#include"SistemConfig.h"
#include"SceneManager.h"
EnemyControl* EnemyControl::GetInstance()
{
	static EnemyControl instance;

	return&instance;
}
void EnemyControl::Load(DebugCamera*camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {

		file.open("Param_CSV/enemy.csv");

		popcom << file.rdbuf();

		file.close();
		/*流れとしては
		敵の数読み込み->
		読み込んだ敵の数分エネミーのパラメータ配列の要素数増やす->
		敵の数分作ったら配列の中身をロードしたものに->
		敵の番号が1だったらα,2だったらβでインスタンス生成、初期化
		*/
		while (std::getline(popcom, line)) {
			std::istringstream line_stream(line);
			std::string word;
			std::getline(line_stream, word, ',');

			if (word.find("//") == 0) {
				continue;
			}
			if (word.find("Enemy_Quantity") == 0) {
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
				if (word.find("Number") == 0) {
					std::getline(line_stream, word, ',');
					int number = (int)std::atof(word.c_str());
					Num[i] = number;
				} else if (word.find("POP") == 0) {
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
		enemys.resize(Quantity);

		Load_EnemyPosition.resize(Quantity);

		for (int i = 0; i < Quantity; i++) {

			//初期化処理
			if (Num[i] == ALPHAENEMY) {
				enemys[i] = std::make_unique<MobEnemy>();
			}
			if (Num[i] == BETAENEMY) {
				enemys[i] = std::make_unique<BossEnemy>();
			}

			enemys[i]->Initialize(camera);
			enemys[i]->SetPosition(pos[i]);
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		tutorial_enemy.resize(1);
		tutorial_enemy[0] = std::make_unique<MobEnemy>();
		tutorial_enemy[0]->Initialize(camera);
		tutorial_pos = { 89.137,-27.5045,-707.987 };
		tutorial_enemy[0]->SetPosition(tutorial_pos);
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::BOSS) {
		boss_enemy.resize(1);
		boss_enemy[0] = std::make_unique<BossEnemy>();
		boss_enemy[0]->Initialize(camera);
		boss_pos = { 0,-27.5045,20.987 };
		boss_enemy[0]->SetPosition(boss_pos);
	}
}

void EnemyControl::TutorialLoad(DebugCamera* camera)
{

}
void EnemyControl::TutorialUpdate(DebugCamera* camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (tutorial_enemy[0] != nullptr) {
			if (TutorialSprite::GetInstance()->GetClearSetting()) {
				tutorial_enemy[0]->SetMoveFlag(true);
				tutorial_enemy[0]->Update(camera);
			}
		}
	}
}

void EnemyControl::TuatorialDraw()
{
	
}
void EnemyControl::Initialize(DebugCamera* camera)
{
	//behavior.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	//behavior.AddNode("Root", "Walk", 1, BehaviorTree::SELECT_RULE::NON, WalkJudgment::GetInstance(), WalkAction::GetInstance());
//

	//behavior.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::NON, EnemyAttackJudgement::GetInstance(), EnemyAttackAction::GetInstance());

	//behavior.AddNode("Root", "Follow", 2, BehaviorTree::SELECT_RULE::NON, FollowJudgement::GetInstance(), FollowAction::GetInstance());
	//behavior.AddNode("Root", "Death", 4, BehaviorTree::SELECT_RULE::NON, DeathJudgment::GetInstance(), DeathAction::GetInstance());

}

void EnemyControl::Update(DebugCamera* camera)
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		for (int i = 0; i < Quantity; i++) {
			if (enemys[i] != nullptr) {
				if (TutorialSprite::GetInstance()->GetClearSetting()) {
					enemys[i]->SetMoveFlag(true);
					enemys[i]->Update(camera);
				}
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (tutorial_enemy[0] != nullptr) {
			tutorial_enemy[0]->SetMoveFlag(true);
				tutorial_enemy[0]->Update(camera);
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::BOSS) {
		if (boss_enemy[0] != nullptr) {
			//boss_enemy[0]->SetMoveFlag(true);
			boss_enemy[0]->Update(camera);
		}
	}
}

void EnemyControl::Draw()
{
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		for (int i = 0; i < Quantity; i++) {
			if (enemys[i] != nullptr) {

				enemys[i]->Draw();
			//	enemys[i]->SearchDraw();
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		if (tutorial_enemy[0] != nullptr) {
			if (TutorialSprite::GetInstance()->GetClearSetting()) {
				tutorial_enemy[0]->Draw();
			}
		}
	}
	if (SceneManager::GetInstance()->GetScene() == SceneManager::BOSS) {
		if (boss_enemy[0] != nullptr) {
			boss_enemy[0]->Draw();
		}
	}
}

void EnemyControl::ImGuiDraw()
{

}

std::vector<std::unique_ptr<Enemy>>& EnemyControl::GetEnemyindex(int index)
{
		return enemys;
}
std::vector<std::unique_ptr<Enemy>>& EnemyControl::GetTutorialEnemyindex()
{
	return tutorial_enemy;
}
std::vector<std::unique_ptr<Enemy>>& EnemyControl::GetBossEnemyindex()
{
	return boss_enemy;
}
void EnemyControl::SetColor(XMFLOAT4 color)
{
	for (int i = 0; i < Quantity; i++) {
		if (enemys[i] != nullptr) {
			enemys[i]->SetColor(color);
		}
	}
}