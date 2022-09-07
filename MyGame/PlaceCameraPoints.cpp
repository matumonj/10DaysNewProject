#include "PlaceCameraPoints.h"
#include"imgui.h"
void PlaceCameraPoints::Initialize(DebugCamera* camera)
{
	Model = Model::CreateFromOBJ("sphere");
	Obj = Object3d::Create(camera);
	Obj->SetModel(Model);
}


void PlaceCameraPoints::Update(DebugCamera* camera)
{
	Obj->SetPosition(pos);
	Obj->SetRotation(rot);
	//Obj->SetScale(scl);
	Obj->Update({ 1,0,0,0.5 }, camera);
}

void PlaceCameraPoints::FileWriting()
{
	file.open("CameraPoints.csv");

	popcom << file.rdbuf();

	file.close();
	///std::ofstream pofs("EnemyParam_CSV/position.csv");
	std::ofstream ofs("EnemyParam_CSV/CameraPoints.csv");  // ファイルパスを指定する
	ofs << "Points_Quantity" << "," << points.size() << std::endl;

	for (int i = 0; i < points.size(); i++) {
		ofs << "POP" << "," << points[i]->GetPosition().x
			<< "," << points[i]->GetPosition().y
			<< "," << points[i]->GetPosition().z << std::endl;
	}
}

void PlaceCameraPoints::ArgMent(DebugCamera* camera)
{
	if (ArgmentFlag) {
		std::unique_ptr<Object3d>newFence;
		if (ArgmentFlag) {
			newFence = std::make_unique<Object3d>();
		}
		newFence->SetModel(Model);
		newFence->Initialize(camera);
		newFence->SetPosition(pos);
		newFence->SetRotation(rot);
		//newFence->SetScale(scl);
		points.push_back(std::move(newFence));
		ArgmentFlag = false;
	}
	for (std::unique_ptr<Object3d>& Fence : points) {
		if (Fence != nullptr) {
			Fence->Update({1,1,1,1},camera);
		}
	}
	if (DeleteFlag && points.size() > 1) {
		points.pop_back();
		DeleteFlag = false;
	}
}
bool PlaceCameraPoints::ErrorJudg()
{
	return false;
}
void PlaceCameraPoints::Draw()
{
	Obj->PreDraw();
	Obj->Draw();
	Obj->PostDraw();
	for (std::unique_ptr<Object3d>& fence : points) {
		if (fence != nullptr) {
			fence->Draw();
		}
	}
}

void PlaceCameraPoints::ImGui_Draw()
{
	ImGui::Begin("Point");
	if (ImGui::Button("Fence", ImVec2(90, 50))) {
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
}