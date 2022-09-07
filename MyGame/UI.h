#pragma once
#include"DebugCamera.h"
#include"HUD.h"
class UI
{
private:

	std::vector<Enemy*>Subenemys;
public:
	static UI* GetInstance();

	void Initialize();

	void HUDUpdate(bool& hudload, DebugCamera* camera);

	void Update(bool&hudload,DebugCamera*camera);

	void HUDDraw();
	void Draw();
	void AreaNameDraw();
};

