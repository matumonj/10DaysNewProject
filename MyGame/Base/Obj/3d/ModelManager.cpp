#include "ModelManager.h"
#include "FbxLoader.h"

std::map<ModelManager::ModelName, Model*> ModelManager::model;
std::map<ModelManager::FBXName, f_Model*>  ModelManager::fbxModel;

ModelManager* ModelManager::GetIns() {
	static ModelManager instans;
	return &instans;
}

void ModelManager::Initialize() {
	LoadModel(Tuna, "Tuna");
	LoadModel(Egg, "Egg");
<<<<<<< HEAD
	LoadModel(Samon, "Samon");
=======
	LoadModel(Dust, "Dust");
	LoadModel(Gate, "Cube");
>>>>>>> 95afcbd988f231e83dd194993ba14c7fbe13f962
	//LoadFBXModel(Enemy_Alpha, "enmeyAlpha");
	//LoadFBXModel(Enemy_Beta, "enemyBeta");
}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName) {
	model[modelName] = new Model();
	model[modelName] = Model::CreateFromOBJ(fileName);
}
void ModelManager::LoadFBXModel(const FBXName modelName, std::string fileName) {
	fbxModel[modelName] = new f_Model();
	fbxModel[modelName] = FbxLoader::GetInstance()->LoadModelFromFile(fileName);
}

