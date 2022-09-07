#pragma once
#include"OBBCollision.h"
#include"ObjectManager.h"
class AreaFence:public ObjectManager
{
public:
	AreaFence() {};
	~AreaFence();

private:
	OBB playerOBB;
	OBB AreaFenceOBB;// = nullptr;
	OBBCollision* ps0 = nullptr;

	float FencePosY_Min;
public:
	void Initialize(DebugCamera* camera)override;
	void Update(DebugCamera* camera)override;
	void Draw()override;
	
	void FenceOpenCondition(bool Condition);
	bool CollideAreaFence();
};

