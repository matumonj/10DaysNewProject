#pragma once
#include"Object3d.h"
#include"Model.h"
#include"DebugCamera.h"
#include<memory>
class TouchableObject;
class CollisionManager;
class Field
{
public:
	Field() {};
	~Field() ;
	static Field* GetInstance();

private:
	TouchableObject* FieldObject;

	std::unique_ptr <Object3d> CelestialSphereObject;

	std::unique_ptr <Object3d> BackObject;

	Model* FieldModel;
	Model* CelestialSphereModel;
	Model* BackM;
public:
	bool Initialize(DebugCamera*camera);
	void Update(DebugCamera* camera);
	void Draw();

};

