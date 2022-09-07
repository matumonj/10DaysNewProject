#include "PlaceFence.h"
#include"imgui.h"
void PlaceFence::Initialize(DebugCamera* camera)
{
	Model = Model::CreateFromOBJ("Fence");
	Obj = Object3d::Create(camera);
	Obj->SetModel(Model);
}

void PlaceFence::FileWriting()
{
	file.open("fence.csv");

	popcom << file.rdbuf();

	file.close();
	///std::ofstream pofs("EnemyParam_CSV/position.csv");
	std::ofstream ofs("EnemyParam_CSV/fence.csv");  // ファイルパスを指定する
	ofs << "Fence_Quantity" << "," << fences.size() << std::endl;

	for (int i = 0; i < fences.size(); i++) {
		ofs << "POP" << "," << fences[i]->GetPosition().x
			<< "," << fences[i]->GetPosition().y
			<< "," << fences[i]->GetPosition().z << std::endl;
		ofs << "ROTATION" << "," << fences[i]->GetRotation().x
			<< "," << fences[i]->GetRotation().y
			<< "," << fences[i]->GetRotation().z << std::endl;
		ofs << "SCALE" << "," << fences[i]->GetScale().x
			<< "," << fences[i]->GetScale().y
			<< "," << fences[i]->GetScale().z << std::endl;

	}
}

bool PlaceFence::ErrorJudg()
{
	return false;
}
void PlaceFence::ArgMent(DebugCamera* camera)
{
	if (ArgmentFlag) {
		std::unique_ptr<AreaFence>newFence;
		if (ArgmentFlag) {
			newFence = std::make_unique<AreaFence>();
		}

		newFence->Initialize(camera);
		newFence->SetPosition(pos);
		newFence->SetRotation(rot);
		newFence->SetScale(scl);
		fences.push_back(std::move(newFence));
		ArgmentFlag = false;
	}
	for (std::unique_ptr<AreaFence>& Fence : fences) {
		if (Fence != nullptr) {
			Fence->Update(camera);
		}
	}
	if (DeleteFlag && fences.size() > 1) {
		fences.pop_back();
		DeleteFlag = false;
	}
}
void PlaceFence::Update(DebugCamera* camera)
{
	Obj->SetPosition(pos);
	Obj->SetRotation(rot);
	Obj->SetScale(scl);
	Obj->Update({ 1,0,0,0.5 }, camera);
}

void PlaceFence::Draw()
{
	Obj->PreDraw();
	Obj->Draw();
	Obj->PostDraw();
	for (std::unique_ptr<AreaFence>& fence : fences) {
		if (fence != nullptr) {
			fence->Draw();
		}
	}
}

void PlaceFence::ImGui_Draw()
{
	ImGui::Begin("Fence");
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
	{
		ImGui::SliderFloat("rotX", &rot.x, 0, 360);
		ImGui::SliderFloat("rotY", &rot.y, 0, 360);
		ImGui::SliderFloat("rotZ", &rot.z, 0, 360);

	}
	{
		ImGui::SliderFloat("sclX", &scl.x, 0, 30);
		ImGui::SliderFloat("sclY", &scl.y, 0, 10);
		ImGui::SliderFloat("sclZ", &scl.z, 0, 10);
	}
	ImGui::End();
}