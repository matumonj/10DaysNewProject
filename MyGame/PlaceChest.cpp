#include "PlaceChest.h"
#include "PlaceChest.h"
#include"imgui.h"
void PlaceChest::Initialize(DebugCamera* camera)
{
	Model = Model::CreateFromOBJ("chest");
	Obj = Object3d::Create(camera);
	Obj->SetModel(Model);
}

void PlaceChest::FileWriting()
{
	file.open("Chest.csv");
	popcom << file.rdbuf();

	file.close();
	///std::ofstream pofs("EnemyParam_CSV/position.csv");
	std::ofstream ofs("EnemyParam_CSV/Chest.csv");  // ファイルパスを指定する
	ofs << "Chest_Quantity" << "," << chests.size() << std::endl;

	for (int i = 0; i < chests.size(); i++) {
		ofs << "POP" << "," << chests[i]->GetPosition().x
			<< "," << chests[i]->GetPosition().y
			<< "," << chests[i]->GetPosition().z << std::endl;

	}
}

bool PlaceChest::ErrorJudg()
{
	return false;
}
void PlaceChest::ArgMent(DebugCamera* camera)
{
	if (ArgmentFlag) {
		std::unique_ptr<Chest>newChest;
		if (ArgmentFlag) {
			newChest = std::make_unique<Chest>();
		}

		newChest->Initialize(camera);
		newChest->SetPosition(pos);
		chests.push_back(std::move(newChest));
		ArgmentFlag = false;
	}
	for (std::unique_ptr<Chest>& chest : chests) {
		if (chest != nullptr) {
			chest->SetColor({ 1,1,1,1 });
			chest->Update(camera);
			chest->CollisionField(camera);
		}
	}
	if (DeleteFlag && chests.size() > 1) {
		chests.pop_back();
		DeleteFlag = false;
	}
}
void PlaceChest::Update(DebugCamera* camera)
{
	Obj->SetPosition(pos);
	Obj->SetScale({ 20,30,20 });
	Obj->Update({ 1,0,0,0.5 }, camera);
}

void PlaceChest::Draw()
{
	for (std::unique_ptr<Chest>& chest : chests) {
		if (chest != nullptr) {
			//enemy->PreDraw();
			chest->Draw();
			//enemy->PostDraw();
		}
	}
	Obj->PreDraw();
	Obj->Draw();
	Obj->PostDraw();

}

void PlaceChest::ImGui_Draw()
{
	ImGui::Begin("Chest");
	if (ImGui::Button("Chest", ImVec2(90, 50))) {
		ArgmentFlag = true;
	}
	ImGui::SameLine();
	
	if (ImGui::Button("DeleteObj", ImVec2(90, 50))) {

		DeleteFlag = true;
	}

	{
		ImGui::SliderFloat("posX", &pos.x, -500, 500);
		ImGui::SliderFloat("posY", &pos.y, -300, 300);
		ImGui::SliderFloat("posZ", &pos.z, -800, 800);

	}
	ImGui::End();
}