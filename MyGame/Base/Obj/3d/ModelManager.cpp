#include "ModelManager.h"
#include "FbxLoader.h"

std::map<ModelManager::ModelName, Model*> ModelManager::model;
std::map<ModelManager::FBXName, f_Model*>  ModelManager::fbxModel;

ModelManager* ModelManager::GetIns() {
	static ModelManager instans;
	return &instans;
}

void ModelManager::Initialize() {
	//LoadFBXModel(Player, "Player");
	LoadModel(Tuna, "Tuna");
	LoadModel(Egg, "Egg");
	LoadModel(Samon, "Samon");
	//LoadFBXModel(Enemy_Alpha, "enmeyAlpha");
	//LoadFBXModel(Enemy_Beta, "enemyBeta");
	//LoadFBXModel(Enemy_Camma, "enemyCamma");
	//LoadFBXModel(Boss_Enemy, "bossEnemy");
}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName) {
	model[modelName] = new Model();
	model[modelName] = Model::CreateFromOBJ(fileName);
}
void ModelManager::LoadFBXModel(const FBXName modelName, std::string fileName) {
	fbxModel[modelName] = new f_Model();
	fbxModel[modelName] = FbxLoader::GetInstance()->LoadModelFromFile(fileName);
}

