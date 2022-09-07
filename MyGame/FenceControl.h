#pragma once
#include "ControlBase.h"
#include"AreaFence.h"
#include<fstream>
#include<string>
#include<sstream>
#include<ostream>
#include <iostream>
#include"Wood.h"
#include"Player.h"
#include"Enemy.h"
#include"DebugCamera.h"
#include<memory>
class FenceControl :
    public ControlBase
{
public:
	~FenceControl() {};
private:
	std::vector<std::unique_ptr<AreaFence>>fences;
	std::vector <XMFLOAT3>Load_FencePosition;
	std::vector<std::unique_ptr<AreaFence>>Tutorialfence;
	XMFLOAT3 Player_OldPos;

	bool TutorialFenceOpen;
private:
	enum {
		TYUTORIAL,
		STAGE1_1,
	};
public:
	static FenceControl* GetInstance();

	void Load(DebugCamera* camera)override;

	void Initialize(DebugCamera* camera)override;

	void Update(DebugCamera* camera)override;

	void Draw()override;

	void SetColor(XMFLOAT4 color)override;
	void ImGuiDraw();

	void SetTutorialFenceOpen(bool judg) { TutorialFenceOpen = judg; }
};

