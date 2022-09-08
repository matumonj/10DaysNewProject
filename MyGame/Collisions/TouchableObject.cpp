#include "TouchableObject.h"
#include "MeshCollider.h"

TouchableObject* TouchableObject::Create(Model* model, DebugCamera* camera)
{
	// オブジェクトのインスタンスを生成
	TouchableObject* instance = new TouchableObject();
	if (instance == nullptr) {
		return nullptr;
	}

	// 初期化
	if (!instance->Initialize(model, camera)) {
		delete instance;
		assert(0);
	}

	return instance;
}

bool TouchableObject::Initialize(Model* model,DebugCamera* camera)
{
	if (!Object3d::Initialize(camera))
	{
		return false;
	}

	SetModel(model);

	// コライダーの追加
	MeshCollider* collider = new MeshCollider;
	SetCollider(collider);
	collider->ConstructTriangles(model);

	return true;
}
