#include "PlaceWood.h"

void PlaceWood::Initialize(DebugCamera* camera)
{
	Model = Model::CreateFromOBJ("wood");
	Obj = Object3d::Create(camera);
	Obj->SetModel(Model);
}

void PlaceWood::FileWriting()
{
	file.open("wood.csv");
	popcom << file.rdbuf();

	file.close();
	///std::ofstream pofs("EnemyParam_CSV/position.csv");
	std::ofstream ofs("EnemyParam_CSV/wood.csv");  // ファイルパスを指定する
	ofs << "Wood_Quantity" << "," << woods.size() << std::endl;

	for (int i = 0; i < woods.size(); i++) {
		ofs << "POP" << "," << woods[i]->GetPosition().x
			<< "," << woods[i]->GetPosition().y
			<< "," << woods[i]->GetPosition().z << std::endl;

	}
}

bool PlaceWood::ErrorJudg()
{
	return false;
}
void PlaceWood::ArgMent(DebugCamera* camera)
{
	if (ArgmentFlag) {
		std::unique_ptr<Wood>newWood;
		if (ArgmentFlag) {
			newWood = std::make_unique<Wood>();
		}

		newWood->Initialize(camera);
		newWood->SetPosition(pos);
		woods.push_back(std::move(newWood));
		ArgmentFlag = false;
	}
	for (std::unique_ptr<Wood>& wood : woods) {
		if (wood != nullptr) {
			wood->SetColor({ 0,1,0,1 });
			wood->Update(camera);
			wood->CollisionField(camera);
		}
	}
	if (DeleteFlag && woods.size() > 1) {
		woods.pop_back();
		DeleteFlag = false;
	}
}
void PlaceWood::Update(DebugCamera* camera)
{
	Obj->SetPosition(pos);
	Obj->SetScale({ 2,3,2 });

	Obj->Update({ 1,0,0,0.5 }, camera);
}

void PlaceWood::Draw()
{
	for (std::unique_ptr<Wood>& wood : woods) {
		if (wood != nullptr) {
			//enemy->PreDraw();
			wood->Draw();
			//enemy->PostDraw();
		}
	}
	Obj->PreDraw();
	Obj->Draw();
	Obj->PostDraw();

}

void PlaceWood::ImGui_Draw()
{
	ImGui::Begin("SelectWood");
	if (ImGui::Button("Wood", ImVec2(90, 50))) {
		ArgmentFlag = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("B", ImVec2(90, 50))) {

	}
	if (ImGui::Button("C", ImVec2(90, 50))) {
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