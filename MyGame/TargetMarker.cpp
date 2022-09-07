#include "TargetMarker.h"
#include"Input.h"
#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include"EnemyControl.h"
#include"SceneManager.h"
TargetMarker::~TargetMarker()
{
	delete TargetMakerTexture;
}
TargetMarker* TargetMarker::GetInstance()
{
	static TargetMarker instance;

	return &instance;
}
void TargetMarker::Initialize()
{
	Texture::LoadTexture(86, L"Resources/target.png");
	TargetMakerTexture = Texture::Create(86, { 0,-50,50 }, { 1,1,1 }, { 1,1,1,1 });
	TargetMakerTexture->CreateTexture();
	TargetMakerTexture->SetAnchorPoint({ 0.5,0.5});
	//MarkerPosition = { -10,2,0 };
}

bool TargetMarker::GetEnemyPosition(std::vector<std::unique_ptr<Enemy>>& enemy, int index, float* x, float* y, float* z)
{
	float tempx, tempy, tempz;
	if (enemy[index] == nullptr||enemy[index]->GetHP()<0) {
	
		return false;
	}
		//指定された添え字の敵座標を取得
		enemy[index]->Getposition(&tempx, &tempy, &tempz);
		*x = enemy[index]->GetPosition().x;
		*y = enemy[index]->GetPosition().y;
		*z = enemy[index]->GetPosition().z;

		return true;
}
int TargetMarker::NearEnemySearch(std::vector<std::unique_ptr<Enemy>>& enemy, Player* player)
{

	int nearindex = -1;
	float nearresult = 0;
	float ex, ey, ez;
	float tx, ty, tz;
	//float distance;
	for (int i = 0; i < enemy.size()/*enemynum*/; ++i) {

		if (!GetEnemyPosition(enemy, i, &ex, &ey, &ez)) {
			//nearindex = -1;
			continue;
		}
		tx = ex - player->GetPosition().x;
		ty = ey - player->GetPosition().y;
		tz = ez - player->GetPosition().z;

		if (nearindex == -1) {
			nearindex = i;
			nearresult = sqrt(tx * tx + ty * ty + tz * tz);
			continue;
		}
		
		//比較して小さければそれを最小値に
		if (nearresult > sqrt(tx * tx + ty * ty + tz * tz)) {
			nearindex = i;	
			nearresult = sqrt(tx * tx + ty * ty + tz * tz);
		//	nearresult2 = nearresult;
		}
		//nearindex2 = nearresult;
		//	if(nearresult)
	}


	this->nearindex = nearindex;
	return nearindex;
}
void TargetMarker::Update(DebugCamera* camera, Player* player)
{
	int tindex;
	float ex, ey, ez;
	if (SceneManager::GetInstance()->GetScene() == SceneManager::PLAY) {
		tindex = NearEnemySearch(EnemyControl::GetInstance()->GetEnemyindex(1), player);
		if (tindex != -1) {
			GetEnemyPosition(EnemyControl::GetInstance()->GetEnemyindex(1), tindex, &ex, &ey, &ez);//{ enemy[0]->GetPosition().x ,0, enemy[0]->GetPosition().z };
		}
	}	
	else if (SceneManager::GetInstance()->GetScene() == SceneManager::TUTORIAL) {
		tindex = NearEnemySearch(EnemyControl::GetInstance()->GetTutorialEnemyindex(), player);
		if (tindex != -1) {
			GetEnemyPosition(EnemyControl::GetInstance()->GetTutorialEnemyindex(), tindex, &ex, &ey, &ez);//{ enemy[0]->GetPosition().x ,0, enemy[0]->GetPosition().z };
		}
	}
	//マーカー位置をnowTargetに合わせる
	MarkerPosition = { ex,ey+10,ez };
	nowTarget = MarkerPosition;

	if (Input::GetInstance()->Pushkey(DIK_L)) {
		MarkerPosition.y += 0.2f;
	}
	if (Input::GetInstance()->Pushkey(DIK_K)) {
		MarkerPosition.y -= 0.2f;
	}

	TargetMakerTexture->Update(camera);
	TargetMakerTexture->SetRotation({180, 0,0
});
	TargetMakerTexture->SetScale({3,3,3});
	TargetMakerTexture->SetPosition(MarkerPosition);
	
}

void TargetMarker::Draw()
{
	if (EnemyTargetDrawFlag) {
	//	TargetMakerTexture->Draw();
	}
}
void TargetMarker::Finalize()
{
	delete TargetMakerTexture;

}