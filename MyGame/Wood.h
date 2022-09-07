
#pragma once
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"

#include"Player.h"
#include<memory>
#include"OBBCollision.h"
#include"ObjectManager.h"
class Wood :public ObjectManager
{

public:
	Wood() {};
	~Wood() ;

private:
	OBB playerOBB;
	OBB woodOBB;// = nullptr;
	OBBCollision* ps0 = nullptr;

public:
	void Initialize(DebugCamera* camera)override;
	void Update(DebugCamera* camera)override;
	void Draw()override;
	bool CollideWood();
};

