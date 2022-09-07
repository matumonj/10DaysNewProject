#pragma once
#include"BaseScene.h"
#include"Audio.h"
#include"Sprite.h"
#include"Input.h"
#include"WinApp.h"

#include"Object3d.h"
#include"Model.h"
#include"Collision.h"
#include"DebugTxt.h"
#include"LightGroup.h"
#include"DebugCamera.h"
#include"DirectXCommon.h"
#include "FbxLoader.h"
#include "f_Object3d.h"
#include"Texture.h"
#include"PostEffect.h"
#include"Enemy.h"
#include"Effects.h"
#include"TargetMarker.h"
#include"GameUI.h"

#pragma comment(lib,"winmm.lib")
class CollisionManager;
class Player;
class MapCreateScene :public BaseScene
{
public:
	//シーンのコンストラクタ
	MapCreateScene(SceneManager* sceneManager);
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

private:
	const float window_width = 1900;
	const float window_height = 1020;
	static const int debugTextTexNumber = 0;
	// デバイス
	static ID3D12Device* device;

	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
private:
	
	XMFLOAT3 CameraPosition;

	DebugCamera* camera;
	
private:
	

private://点光源
	
public:
	void ModelCreate(DebugCamera* camera);
	void MyGameDraw();
	void objUpdate(DebugCamera* camera);

public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	
	void SpriteDraw();
	void ImGuiDraw();
	void Finalize()override;

private:
	PostEffect* postEffect = nullptr;
	int c_postEffect;
private:
	enum {
		Blur,
		Default,
	};
	
	bool t, y;

private:
	LightGroup* lightGroup = nullptr;
	float ambientColor0[3] = { 1,1,1 };

	float lightDir0[3] = { 0,0,1 };
	float lightColor0[3] = { 1,0,0 };

	float lightDir1[3] = { 0,1,0 };
	float lightColor1[3] = { 0,1,0 };

	float lightDir2[3] = { 1,0,0 };
	float lightColor2[3] = { 0,0,1 };

	float pointLightPos[3] = { 0,0,-50 };
	float pointLightColor[3] = { 1,1,1 };
	float pointLightAtten[3] = { 0.05f,0.05f,0.05f };

	float SpotLightPos[3] = { 10,0,0 };
	float SpotLightColor[3] = { 1,1,1 };

	CollisionManager* collisionManager = nullptr;
};

