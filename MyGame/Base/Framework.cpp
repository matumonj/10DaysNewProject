#include "Framework.h"
#include "ModelManager.h"

void Framework::Run()
{
	Initialize();

	while (true) {
		//ウィンドウメッセージ処理
		Update();

		//終了リクエストが来たら抜ける
		if (IsEndRequst()) {
			break;
		}

		Draw();
	}
	//Finalize();
}
/// <summary>
/// 初期化
/// </summary>
void Framework::Initialize()
{
	//共通部分のインスタンス生成と初期化
	winapp = new WinApp();
	winapp->Createwindow();
	DirectXCommon::GetInstance()->Initialize(winapp);
	input = Input::GetInstance();
	input->Initialize(winapp);
	audio = new Audio();
	// ライト静的初期化
	Object3d::StaticInitialize(WinApp::window_width, WinApp::window_height);
	ModelManager::GetIns()->Initialize();
	//MyGame* MyGame = new MyGame();
	sceneManger = new SceneManager();
	
}

/// <summary>
/// 更新
/// </summary>
void Framework::Update()
{
	if (winapp->Processmassage()) {
		winRequest = true;
		return;
	}
	input->update();
	sceneManger->Update();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void Framework::Draw()
{
	sceneManger->Draw();
}

void Framework::Finalize()
{
	FbxLoader::GetInstance()->Finalize();
	//delete sceneManger;
	delete audio;
	//delete dxcomn;
	delete input;
	delete winapp;
}