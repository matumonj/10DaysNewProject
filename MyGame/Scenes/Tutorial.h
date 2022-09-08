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
#include"ControlBase.h"

#pragma comment(lib,"winmm.lib")
class CollisionManager;
class Player;
class Tutorial :public BaseScene
{
public:
	//シーンのコンストラクタ
	Tutorial(SceneManager* sceneManager);
	//~Tutorial();
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
	
private:
	Input* input;
	int obbf = 0;
	unsigned long prev_time = timeGetTime();
	int count_frame = 0;
float ty;
	float cameraAngle = -90;
	float charaAngle = 0;
	XMFLOAT3 CameraPosition;

	bool scenechange;
	bool feedflag;
	XMFLOAT4 feedcolor = { 0,0,0,1 };
	PostEffect* postEffect = nullptr;
private:
	float u;
	XMFLOAT3 Player_Pos;// = player->GetPosition();
	XMFLOAT3 Player_Rot;// = player->GetRotation();

	float distance = 30;

	float dy;
	float dx;
	float dz;

private://点光源
	
public:
	void MyGameDraw();
	void objUpdate(DebugCamera* camera);

public:
	XMFLOAT3 texpo = { 0,0,0 };
	void Initialize()override;
	void Update()override;
	void Draw()override;
	bool LoadParam(DebugCamera* camera);
	void SpriteDraw();
	void ImGuiDraw();
	void Finalize()override;
public:
	XMFLOAT3 efkposition = { -50,-10,90 };
	//エフェクト用(ただプログラムでつくれるものはプログラムで作る方がいい　多用はいくない)
	int c_postEffect = Default;
private:
	enum {
		Blur,
		Default,
	};
	bool Play;
	POINT p;
	CollisionManager* collisionManager = nullptr;
	bool hudload;
	float CameraDis = 25;
	float CameraHeight = 9;
private:
	//デバッグ用変数 後々消すやつ
	bool LoadEnemy;
	bool turnoff_player;
	bool turnoff_enemy;

	float p_alpha = 1;
	float e_alpha = 1;

	bool CameraViewPoint_First = true;
	bool CameraViewPoint_Third;
	bool t, y;

private:
	std::vector<ControlBase*>AllObjectControl;
};

