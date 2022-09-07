#pragma once
#include"AreaFence.h"
#include "CreateObjManager.h"
class PlaceFence :public CreateObjManager
{
public:

	void Initialize(DebugCamera* camera)override;

	void Update(DebugCamera* camera)override;

	void ImGui_Draw()override;

	void FileWriting()override;

	void ArgMent(DebugCamera* camera)override;

	void Draw()override;

	bool ErrorJudg()override;

private:
	std::vector<std::unique_ptr<AreaFence>>fences;
};

