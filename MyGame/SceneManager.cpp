#include "SceneManager.h"
SceneManager* SceneManager::GetInstance()
{
	static SceneManager instance;
	return &instance;
}
/// <summary>
/// 更新
/// </summary>
void SceneManager::Update()
{
	if (nextScene) {
		if (Scene) {//前のシーンを破棄
			Scene->Finalize();
			delete Scene;
		}
		//次のシーンへ移行
		Scene = nextScene;
		nextScene = nullptr;
		
		Scene->Initialize();//移行したら初期化
	}
	//更新
	Scene->Update();
}

/// <summary>
/// 描画
/// </summary>
/// <param name="cmdList"></param>
void SceneManager::Draw()
{
	Scene->Draw();
}
