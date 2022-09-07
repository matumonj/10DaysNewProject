#include "PlaceEnemy.h"
#include "PlaceEnemy.h"
#include "PlaceEnemy.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
void PlaceEnemy::Initialize(DebugCamera* camera)
{
	Model = Model::CreateFromOBJ("box");
	Obj = Object3d::Create(camera);
	Obj->SetModel(Model);
}

bool PlaceEnemy::ErrorJudg()
{
	const int Min_EnemySize = 2;//設置できる敵の最小数
	const int Max_EnemySize = 30;//設置できる敵の最大数

	if (enemys.size() < Min_EnemySize||enemys.size()>Max_EnemySize) {
		return true;
	}
	return false;
}
void PlaceEnemy::FileWriting()
{
	
	file.open("enemy.csv");

	popcom << file.rdbuf();

	file.close();
	std::ofstream pofs("Param_CSV/position.csv");
	std::ofstream ofs("Param_CSV/enemy.csv");  // ファイルパスを指定する
	ofs << "Enemy_Quantity" << "," << enemys.size() << std::endl;

	for (int i = 0; i < enemys.size(); i++) {
		ofs << "Wait" << "," << 120 << std::endl;
		ofs << "Number" << "," << Number[i] << std::endl;
		ofs << "POP" << "," << enemys[i]->GetPosition().x
			<< "," << enemys[i]->GetPosition().y
			<< "," << enemys[i]->GetPosition().z << std::endl;

	}
}

void PlaceEnemy::ArgMent(DebugCamera* camera)
{
	if (ArgmentFlag || BossArgmentFlag) {

		std::unique_ptr<Enemy>newEnemy;
		if (ArgmentFlag) {
			newEnemy = std::make_unique<MobEnemy>();
		}
		if (BossArgmentFlag) {
			newEnemy = std::make_unique<BossEnemy>();
		}
		newEnemy->Initialize(camera);
		newEnemy->SetPosition(pos);
		enemys.push_back(std::move(newEnemy));
		if (ArgmentFlag) {
			Number.push_back(1);
		}
		ArgmentFlag = false;
		BossArgmentFlag = false;
	}
	for (std::unique_ptr<Enemy>& enemy : enemys) {
		if (enemy != nullptr) {
			enemy->Update( camera);
		}
	}
	if (DeleteFlag && enemys.size() > 1) {
		enemys.pop_back();
		Number.pop_back();
		DeleteFlag = false;
	}
}
void PlaceEnemy::Update(DebugCamera* camera)
{
	Obj->SetPosition(pos);
	Obj->SetScale({ 2,3,2 });
	Obj->SetColor({ 1,0,0,1 });
	Obj->Update({ 1,0,0,0.5 }, camera);
}

void PlaceEnemy::Draw()
{
	Obj->PreDraw();
	Obj->Draw();
	Obj->PostDraw();
	for (std::unique_ptr<Enemy>& enemy : enemys) {
		if (enemy != nullptr) {
			enemy->Draw();
		}
	}
}

void PlaceEnemy::ImGui_Draw()
{
	ImGui::Begin("SelectEnemy");
	if (ImGui::Button("AlphaEnemy", ImVec2(90, 50))) {
		ArgmentFlag = true;
		Number.push_back(1);
	}
	ImGui::SameLine();
	if (ImGui::Button("BetaEnemy", ImVec2(90, 50))) {
		BossArgmentFlag = true;
		Number.push_back(2);
	}
	ImGui::SameLine();
	if (ImGui::Button("CammaEnemy", ImVec2(90, 50))) {
	}
	ImGui::SameLine();


	if (ImGui::Button("DeleteObj", ImVec2(90, 50))) {
		DeleteFlag = true;
	}
	const char* l[] = { "aaa","bbb","ccc","ddd" };
	static int lc = 1;
	ImGui::ListBox("list\n(ki)", &lc, l, IM_ARRAYSIZE(l), 4);
	{
		ImGui::SliderFloat("posX", &pos.x, -300, 300);
		ImGui::SliderFloat("posY", &pos.y, -300, 300);
		ImGui::SliderFloat("posZ", &pos.z, -800, 800);

	}

}