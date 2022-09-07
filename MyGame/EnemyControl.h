#include "ControlBase.h"
#include<fstream>
#include<string>
#include<sstream>
#include<ostream>
#include <iostream>
#include"Enemy.h"
#include"DebugCamera.h"
#include<memory>
class EnemyControl :
    public ControlBase
{
public:
	~EnemyControl() {};
private:
	//std::unique_ptr<Player>player;
	std::vector<std::unique_ptr<Enemy>>enemys;
	std::vector <XMFLOAT3>Load_EnemyPosition;
	//チュートリアル用
	std::vector <std::unique_ptr<Enemy>> tutorial_enemy;
	//ボス用
	std::vector <std::unique_ptr<Enemy>> boss_enemy;

	XMFLOAT3 tutorial_pos;
	XMFLOAT3 boss_pos;
	
private:
	enum {
		ALPHAENEMY=1,
		BETAENEMY=2,
	};
public:
	static EnemyControl* GetInstance();

	void Load(DebugCamera*camera)override;

	void Initialize(DebugCamera* camera)override;

	void Update(DebugCamera* camera)override;

	void Draw()override;

	void TutorialLoad(DebugCamera* camera);
	void TutorialUpdate(DebugCamera* camera);

	void TuatorialDraw();

	void ImGuiDraw();

	void SetColor(XMFLOAT4 color)override;
	std::vector<std::unique_ptr<Enemy>> &GetEnemyindex(int index);// { return enemys[index].get(); }
	std::vector <std::unique_ptr<Enemy>> &GetTutorialEnemyindex();
	std::vector <std::unique_ptr<Enemy>>& GetBossEnemyindex();
private:
	//::vector<Enemy*>
};

