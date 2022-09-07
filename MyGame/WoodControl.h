#pragma once
#include "ControlBase.h"

#include"Wood.h"
#include"Enemy.h"
#include"Player.h"
#include"DebugCamera.h"
#include<memory>
class WoodControl :
    public ControlBase
{
	~WoodControl();
private:
	std::vector<std::unique_ptr<Wood>>woods;
	std::vector <XMFLOAT3>Load_WoodPosition;

	XMFLOAT3 Player_OldPos;
	std::vector<std::unique_ptr<Wood>>Tutorialwoods;

public:
	static WoodControl* GetInstance();

	void Load(DebugCamera* camera)override;

	void Initialize(DebugCamera* camera)override;

	void Update(DebugCamera* camera)override;

	void Draw()override;

	void SetColor(XMFLOAT4 color)override;

	void ImGuiDraw();
};

