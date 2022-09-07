#pragma once
#include<d3d12.h>
#include<d3dx12.h>
#include<dxgi1_6.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>
#include<dinput.h>
#include<dinput.h>

#include<DirectXTex.h>
#include<wrl.h>
#include"DirectXCommon.h"
//‚Ü‚Á‚Â‚ñƒz[ƒ€‰˜‚·‚¬
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"d3d12.lib")

#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
class SceneManager;
class BaseScene
{
public:
	BaseScene(SceneManager* sceneManager);
	//~BaseScene();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Finalize() = 0;
	//virtual void SpriteDraw(ID3D12GraphicsCommandList* cmdList) = 0;
protected:
	SceneManager* sceneManager_ = nullptr;
};

