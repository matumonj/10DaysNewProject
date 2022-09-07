#include "MapCreate.h"
#include"MobEnemy.h"
#include"BossEnemy.h"
#include"PlaceFence.h"
#include"PlaceWood.h"
#include"PlaceEnemy.h"
#include"PlaceChest.h"
#include"PlaceCameraPoints.h"
MapCreate::MapCreate()
{

}

MapCreate* MapCreate::GetInstance()
{
	static MapCreate instance;
	return &instance;
}

void MapCreate::ObjectInitialize(DebugCamera* camera)
{
	//ここに設置物newしていくだけ
	//注意：面倒だけど要素の追加は列挙型に合わせる[FENCE=0,WOOD=1,ENEMY=2] errorWindow処理で使う為
	if (placeobj.size() == 0) {//create->playscene->createといったときに二回newされるの防ぐ
		placeobj.push_back(new PlaceFence());//柵
		placeobj.push_back(new PlaceWood());//木
		placeobj.push_back(new PlaceEnemy());//敵
		placeobj.push_back(new PlaceChest());
		placeobj.push_back(new PlaceCameraPoints());
	}
	for (int i = 0; i < placeobj.size(); i++) {
		placeobj[i]->Initialize(camera);//モデル用意、初期化
	}
}
void MapCreate::ObjectUpdate(DebugCamera* camera)
{
	for (int i = 0; i < placeobj.size(); i++) {
		placeobj[i]->Update(camera);//モデル更新
	}
}

void MapCreate::ObjectArgment(DebugCamera* camera)
{
	if (savef) {
		if (!Error()) {//もし何か一つでもエラー条件に当てはまったらファイルへの書き込みしない
			for (int i = 0; i < placeobj.size(); i++) {
				placeobj[i]->FileWriting();//csvへの書き込み
			}
		}
		savef = false;
	}


	for (int i = 0; i < placeobj.size(); i++) {
		placeobj[i]->ArgMent(camera);//配置オブジェクトの設置、更新
	}
}

void MapCreate::ImGuiDraw()
{	//ImGui描画周り
	for (int i = 0; i < placeobj.size(); i++) {
		placeobj[i]->ImGui_Draw();
	}
	ImGui::Begin("SaveButton");
	if (ImGui::Button("Save", ImVec2(90, 50))) {
		savef = true;//オブジェクトのパラメータ保存フラグ
	}
	ImGui::End();
}
void MapCreate::ObjectDraw()
{
	for (int i = 0; i < placeobj.size(); i++) {
		placeobj[i]->Draw();//モデル、設置物の描画
	}
}


bool MapCreate::Error()
{
	//エラーウィンドウ処理
	if (placeobj[FENCE]->ErrorJudg() || placeobj[WOOD]->ErrorJudg() || placeobj[2]->ErrorJudg()) {
		WinApp::CreateErrorWindow(placeobj[ENEMY]->ErrorJudg(), TEXT("敵を1体以上配置してください"));
		WinApp::CreateErrorWindow(placeobj[FENCE]->ErrorJudg(), TEXT("柵を1個以上配置してください"));
		WinApp::CreateErrorWindow(placeobj[WOOD]->ErrorJudg(), TEXT("木を1本以上配置してください"));
		WinApp::CreateErrorWindow(placeobj[CHEST]->ErrorJudg(), TEXT("宝箱は必ず5つ配置してください"));
		return true;
	}
	return false;
}
