#include "NormalSword.h"
#include"PlayerControl.h"
NormalSword::~NormalSword()
{
	//delete  m_Model;
}
void NormalSword::Initialize(DebugCamera* camera)
{
	m_Object = std::make_unique<Object3d>();

	m_Model = Model::CreateFromOBJ("sword");

	//フィールドにモデル割り当て
	m_Object->Initialize(camera);
	m_Object->SetModel(m_Model);

	Scale = { 1,1,1 };

	Rotation = { 0,0 + 30,0 + 100 };
	DamageArea.scale = Radius;
}

void NormalSword::Update(DebugCamera* camera)
{
	const float Damage_Value = 5.0f;
	const float CoolTime_Value = 60.0f;

	Damage = Damage_Value;
	CoolTime = CoolTime_Value;
	//m_Object->SetParent(PlayerControl::GetInstance()->GetPlayer()->GetHanMat());
	m_Object->SetRotation(Rotation);
	m_Object->Update(PlayerControl::GetInstance()->GetPlayer()->GetHanMat(), { 1,1,1,1 }, camera);

}

void NormalSword::Draw()
{
	Draw_Obj();
}