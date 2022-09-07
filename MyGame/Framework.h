#pragma once

#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"
#include"Object3d.h"
#include"SceneManager.h"
#include "FbxLoader.h"
class Framework
{
public:
	void Run();
	virtual void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void Finalize();
	//virtual void SpriteDraw()=0;
	bool IsEndRequst() { return winRequest; }
protected:
	//IScene * Scene;
	bool winRequest = false;
	WinApp* winapp = nullptr;
	Input* input = nullptr;
	//DirectXCommon* dxcomn = nullptr;
	Audio* audio = nullptr;
	SceneManager* sceneManger = nullptr;
	//Sprite* sprite = nullptr;
};

