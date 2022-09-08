#include "Player.h"
#include"Input.h"
#include"DebugTxt.h"
#include"SphereCollider.h"
#include"Collision.h"
#include"SphereCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"
#include"imgui.h"
#include"WoodControl.h"
#include"SceneManager.h"
#define PI 3.145265
using namespace DirectX;
XMFLOAT3 Player::Effect_Pos = { -50,-10,-100 };

Player::~Player()
{
	delete fbxmodel;
	delete  m_Model;
}
Player* Player::GetInstance()
{
	static Player instance;

	return &instance;
}

Player* Player::Create(Model* model, DebugCamera* camera)
{
	return Player::GetInstance();
}

void Player::Initialize(DebugCamera* camera)
{
	HP = MaxHP;
	rotate = RotationPrm::FRONT;

	m_Object = std::make_unique<Object3d>();
	m_Object->Initialize(camera);
	m_fbxModel = FbxLoader::GetInstance()->LoadModelFromFile("monster_golem_demo");

	m_fbxObject = std::make_unique<f_Object3d>();
	m_fbxObject->Initialize();
	m_fbxObject->SetModel(m_fbxModel);
	m_fbxObject->PlayAnimation();

	SetCollider();

	Rotation = { -90,0,0 };
	Position = { 0,-30,0 };
}
void Player::Update(DebugCamera* camera)
{
	oldpos = Position;
	//エフェクトのパラメータセット
	RotationStatus();
	//Position.y = -2;
	Scale={ 0.02, 0.02f, 0.02f
		};
	//
	// 
	//Position = { 92,-27,-760 };
	//移動ベクトルをy軸周りの角度で回転
	XMVECTOR move = { 0.0f,0.0f,0.1f,0.0f };
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(Rotation.y));
	move = XMVector3TransformNormal(move, matRot);

	if (input->Pushkey(DIK_W) || input->Pushkey(DIK_A) || input->Pushkey(DIK_D) || input->Pushkey(DIK_S)
		|| (input->LeftTiltStick(input->Left) || input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Up) || input->LeftTiltStick(input->Down))) {
		Position.x += move.m128_f32[0] * movespeed;
		Position.z += move.m128_f32[2] * movespeed;
		
		stopf = false;
	} else {
		stopf = true;
		
	}
	Gmove = move;
	FbxAnimationControl();
	//フィールド
	ParameterSet_Obj(camera);
	//フィールド
	ParameterSet_Fbx(camera);

	CollisionField(camera);

	HandMat = m_fbxObject->GetRot();
}

void Player::RotationStatus()
{

	//左方向への移動
	if (rotate != RotationPrm::LEFT && input->LeftTiltStick(input->Left)) {//今向いている方向が左じゃなくAキーが押され、
		if (rotate == RotationPrm::FRONT) {//右以外を向いていたら
			Rotation.y = Rotation.y - 90;
		} else if (rotate == RotationPrm::BACK) {//右を向いていたら
			Rotation.y = Rotation.y + 90;
		} else if (rotate == RotationPrm::RIGHT) {
			Rotation.y = Rotation.y - 180;
		}
		//向きの情報を左に
		rotate = RotationPrm::LEFT;
	}

	//右方向への移動
	else if (rotate != RotationPrm::RIGHT && input->LeftTiltStick(input->Right)) {//今向いている方向が右じゃなくＤキーが押され、
		if (rotate == RotationPrm::FRONT) {//右以外を向いていたら
			Rotation.y = Rotation.y + 90;
		} else if (rotate == RotationPrm::BACK) {//右を向いていたら
			Rotation.y = Rotation.y - 90;
		} else if (rotate == RotationPrm::LEFT) {
			Rotation.y = Rotation.y + 180;
		}
		//向きの情報を右に
		rotate = RotationPrm::RIGHT;
	}

	//前方向への移動
	if (rotate != RotationPrm::FRONT && input->LeftTiltStick(input->Up)) {//今向いている方向が右じゃなくＤキーが押され、
		if (rotate == RotationPrm::RIGHT) {//もし右を向いてたら
			Rotation.y = Rotation.y - 90;
		} else if (rotate == RotationPrm::LEFT) {//もし左を向いてたら
			Rotation.y = Rotation.y + 90;
		} else if (rotate == RotationPrm::BACK) {
			Rotation.y -= 180;
		}
		//向きの情報を前に
		rotate = RotationPrm::FRONT;
	}

	//後ろ方向へ移動
	if (rotate != RotationPrm::BACK && input->LeftTiltStick(input->Down)) {//今向いている方向が右じゃなくＤキーが押され、
		if (rotate == RotationPrm::RIGHT) {//もし右を向いてたら
			Rotation.y = Rotation.y + 90;
		} else if (rotate == RotationPrm::LEFT) {//もし左を向いてたら
			Rotation.y = Rotation.y - 90;
		} else if (rotate == RotationPrm::FRONT) {
			Rotation.y += 180;
		}
		//向きの情報を前に
		rotate = RotationPrm::BACK;
	}
}


void Player::Draw()
{
	Draw_Fbx();
}

void Player::ImguiDraw()
{
	//ImGui::Begin("Player_State");
	//if (ImGui::TreeNode("Position")) {

	//	ImGui::Text(" PositionX   [%5f]", Position.x);
	//	ImGui::Text(" PositionY   [%5f]", Position.y);
	//	ImGui::Text(" PositionZ   [%5f]", Position.z);

	//}
	////Rotation
	//if (ImGui::TreeNode("Rotation")) {
	//	XMMATRIX sub = m_fbxObject->GetPos();

	//	XMFLOAT3 rots = { sub.r[3].m128_f32[0],sub.r[3].m128_f32[1], sub.r[3].m128_f32[2] };
	//	ImGui::Text(" RotationX   [%5f]", rots.x);
	//	ImGui::Text(" RotationY   [%5f]", rots.y);
	//	ImGui::Text(" RotationZ   [%5f]", rots.z);
	//	ImGui::TreePop();
	//}
	//ImGui::SliderInt("HP", &HP, 1, MaxHP);
	//ImGui::SliderFloat("MoveSpeed", &movespeed, 1, 15);
	////もし落下したとき地面に戻ってくる 1秒前の接地位置に戻ってくる
	//PosSavetime++;
	//if (PosSavetime > 60) {
	//	PosSavetime = 0;
	//}
	//if (ImGui::RadioButton("ReturnGround", &ReturnGround)) {
	//	Position = OldPos_Onground;
	//	ReturnGround = false;
	//}
	
	ImGui::End();
}

void Player::FbxAnimationControl()
{
	if (AttackFlag) {
		f_time = AttackTime;
		AttackFlag = false;
		nowattack = true;
	}


	f_time += 0.02f;
	if (nowattack) {
		if (f_time >= DeathTime) {
			f_time = 0;
			nowattack = false;
		}
	} else {
		if (f_time > AttackTime) {
			f_time = 0;
		}
	}


	m_fbxObject->SetFbxTime(f_time);
}

void Player::SetColors(XMFLOAT4 color)
{
	m_fbxObject->SetColor(color);
}

XMMATRIX Player::GetMatrot()
{
	if (m_fbxObject != nullptr) {
		return m_fbxObject->GetMatrot();
	}
}