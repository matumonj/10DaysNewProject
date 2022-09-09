#include "Human.h"

void Human::Initialize() {

	m_fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("Human");

	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(m_fbxModel);
	m_fbxObject->PlayAnimation();

//	FbxAnimationControl();

}

void Human::Update() {




}

void Human::Draw() {
	//m_fbxObject->Pre
	//m_fbxObject->Draw();


}

//void Player::FbxAnimationControl() {
//	if (AttackFlag) {
//		f_time = AttackTime;
//		AttackFlag = false;
//		nowattack = true;
//	}
//
//
//	f_time += 0.02f;
//	if (nowattack) {
//		if (f_time >= DeathTime) {
//			f_time = 0;
//			nowattack = false;
//		}
//	} else {
//		if (f_time > AttackTime) {
//			f_time = 0;
//		}
//	}
//
//
//	m_fbxObject->SetFbxTime(f_time);
//}
