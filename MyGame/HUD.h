#pragma once
#include"Enemy.h"
#include"Sprite.h"
#include"Player.h"
#include<memory>
#include<vector>
class HUD
{
public:
	~HUD();
	static HUD* GetInstance();
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::‚ðÈ—ª
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	using XMVECTOR = DirectX::XMVECTOR;

	Sprite* PlayerHP;
	float CoolTime_Time = 0;
	float TimeSpeed;
public:
	float GetSpriteSize(int index) { return coolDownSprite[index]->GetSize().y; }
	bool GetLayOutMode();
	void SetPosition_PlayerHP(XMFLOAT2 position);
	void SetAnchor_PlayerHP(XMFLOAT2 position);
	Sprite* GetPlayerHP() { return PlayerHP; }
	Sprite* GetEnemyHP() { return EnemyHP_Border; }
	XMFLOAT2 GetSkillButtonPosition() { return CenterPosition; }

public:
	void Initialize();
	void Update();
	void Draw();
public://“G‘Ì—Í‚ÌHUD
	Sprite* EnemyHP_Border;
	Sprite* EnemyHP_Inner;
	void EnemyHPGaugeInitialize();
	void EnemyHPGaugeUpdate(std::vector<std::unique_ptr<Enemy>>& enemy);
	void EnemyHPGaugeDraw();
	Sprite* TaskSprite;
	float taskAlpha = 0;
	XMFLOAT2 taskSpriteSize;
	bool taskfeed;
	std::vector<Texture*> EnemyHP_Border_Multi;
	std::vector<Texture*>EnemyHP_Inner_Multi;
	void EnemyHPGauge_MultiInitialize();
	void EnemyHPGauge_MultiUpdate(bool& loadf,DebugCamera*camera, std::vector<std::unique_ptr<Enemy>>& enemy);
	void EnemyHPGauge_MultiDraw();
public:
	XMFLOAT2 GetCenterPosition() { return CenterPosition; }
	void SetCenterPosition(XMFLOAT2 pos) { CenterPosition = pos; }
	Sprite* GetSkillButton() { return FirstAttackSprite; }
	XMFLOAT2 CenterPosition = {1050,500};
	Sprite* coolDownSprite[4];
	Sprite* FirstAttackSprite;
	Sprite* SecondAttackSprite;
	Sprite* ThirdAttackSprite;
	Sprite* BuffSprite;

	XMFLOAT2 CooltimeSize;
	void SkillButtonInitialize();
	void SkillBottonUpdate();
	void TaskUpdate(DebugCamera* camera);
	void SkillBottonDraw();
	void ChangePosition(XMFLOAT2 MousePosition, XMFLOAT2& c);
	void AreaName();
	bool f;
	float nowhp;
	XMFLOAT2 sizel;
	float oldhp;
	float Hpt;

	bool EnemyHPDrawFlag;
	//bool load;
	std::vector<float> multi_NowHP;
	std::vector <XMFLOAT3> multi_sizel;
	std::vector<float> multi_OldHP;
	std::vector<float> multi_Hpt;
	std::vector<float>Alpha;


};

