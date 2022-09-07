#pragma once
#include"Player.h"
#include"Enemy.h"
#include"BossEnemy.h"
#include"MobEnemy.h"
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include"Texture.h"
#include"DirectXCommon.h"
#include"DebugCamera.h"
class TargetMarker
{
public:
	~TargetMarker();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

public:
	static TargetMarker* GetInstance();
	bool GetEnemyPosition(std::vector<std::unique_ptr<Enemy>>& enemy, int index, float* x, float* y, float* z);
	int NearEnemySearch(std::vector<std::unique_ptr<Enemy>>& enemy, Player* player);
	void Initialize();
	void Update(DebugCamera* camera, Player* player);
	void Draw();
	void Finalize();
private:
	int TargetDecision;
	XMFLOAT3 TargetDecisionPos;
	float* length_x;
	float* length_y;
	float* length_z;
	XMFLOAT3 MarkerPosition;
	XMFLOAT3 nowTarget;
	float rot = 90;
	//Player* player = nullptr;
	int nearindex = -1;
	int nearindex2 = -1;
	float nearresult2;
	std::vector<Enemy*> enemy = { nullptr };
	Texture* TargetMakerTexture = nullptr;
	bool EnemyTargetDrawFlag;


public:
	void SetTargetMarkerDraw(bool f) { EnemyTargetDrawFlag = f; }
	int GetNearIndex2() { return nearindex2; }
	int GetNearIndex() { return nearindex; }
	XMFLOAT3 GetMarkerPosition() { return MarkerPosition; }
	int GetTargetEnemyindex() { return nearindex; }
	XMFLOAT3 Getpos() { return MarkerPosition; }
	void Setpos(float y) { MarkerPosition.y = y; }
};

