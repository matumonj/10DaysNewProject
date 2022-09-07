#pragma once
#include"Player.h"
#include "ControlBase.h"
class PlayerControl :
    public ControlBase
{
public:
	~PlayerControl() {};
private:
	std::unique_ptr<Player>player;
	
	XMFLOAT3 Player_OldPos;

	bool TutorialFenceOpen;
private:
	enum {
		TYUTORIAL,
		STAGE1_1,
	};
public:
	static PlayerControl* GetInstance();

	void Load(DebugCamera* camera)override;

	void Initialize(DebugCamera* camera)override;

	void Update(DebugCamera* camera)override;

	void Draw()override;

	void SetColor(XMFLOAT4 color)override;
	void ImGuiDraw();


	Player* GetPlayer() { return player.get(); }

};

