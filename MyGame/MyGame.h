#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>
// DirectInputバージョンの宣言
#define DIRECTINPUT_VERSION 0x0800
#include  <dinput.h>
#include<DirectXTex.h>
#include<wrl.h>

//まっつんホーム汚すぎ
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")

#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"
#include"Texture.h"
#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"BaseScene.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"Framework.h"
#include"GameScene.h"
#include"ResultScene.h"
#include"DirectXCommon.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class MyGame : public Framework
{
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	//void SpriteDraw()override;
	void Finalize()override;
	void backGround();
private:
	bool t = false, y = false;
	//PlayScene* Scene;
	//IScene* Scene;
};

