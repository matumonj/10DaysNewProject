#pragma once
#include "AreaFence.h"
#include"PlayerControl.h"

AreaFence::~AreaFence()
{
	//delete  m_Model;
	delete ps0;
}
void AreaFence::Initialize(DebugCamera* camera)
{
	m_Object = std::make_unique<Object3d>();

	m_Model = Model::CreateFromOBJ("Fence");

	//フィールドにモデル割り当て
	m_Object->Initialize(camera);
	m_Object->SetModel(m_Model);
	ps0 = new OBBCollision();

	Scale = { 10,10,10 };

}

void AreaFence::Update(DebugCamera* camera)
{
	CollideAreaFence();
	//フィールド
	ParameterSet_Obj(camera);
}

void AreaFence::Draw()
{
	Draw_Obj();
}

bool AreaFence::CollideAreaFence()
{
	playerOBB.m_NormaDirect[0] = { PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[0].m128_f32[0],PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[0].m128_f32[1],PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[0].m128_f32[2] };
	playerOBB.m_NormaDirect[1] = { PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[1].m128_f32[0],PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[1].m128_f32[1],PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[1].m128_f32[2] };
	playerOBB.m_NormaDirect[2] = { PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[2].m128_f32[0],PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[2].m128_f32[1],PlayerControl::GetInstance()->GetPlayer()->GetMatrot().r[2].m128_f32[2] };
	playerOBB.m_fLength[0] = 1;//x方向の長さ
	playerOBB.m_fLength[1] = 1;//y方向の長さ
	playerOBB.m_fLength[2] = 1;//z方向の長さ
	//敵のOBB 回転ベクトル
	AreaFenceOBB.m_NormaDirect[0] = { m_Object->GetMatrot().r[0].m128_f32[0],m_Object->GetMatrot().r[0].m128_f32[1],m_Object->GetMatrot().r[0].m128_f32[2] };
	AreaFenceOBB.m_NormaDirect[1] = { m_Object->GetMatrot().r[1].m128_f32[0], m_Object->GetMatrot().r[1].m128_f32[1], m_Object->GetMatrot().r[1].m128_f32[2] };
	AreaFenceOBB.m_NormaDirect[2] = { m_Object->GetMatrot().r[2].m128_f32[0], m_Object->GetMatrot().r[2].m128_f32[1], m_Object->GetMatrot().r[2].m128_f32[2] };
	AreaFenceOBB.m_fLength[0] = m_Object->GetMatScl().r[0].m128_f32[0] * 4;
	AreaFenceOBB.m_fLength[1] = m_Object->GetMatScl().r[1].m128_f32[1] * 3;//y方向の長さ
	AreaFenceOBB.m_fLength[2] = m_Object->GetMatScl().r[2].m128_f32[2] - 2;//z方向の長さ
	//OBBの設定位置
	playerOBB.m_Pos = { PlayerControl::GetInstance()->GetPlayer()->GetPosition().x,PlayerControl::GetInstance()->GetPlayer()->GetPosition().y,PlayerControl::GetInstance()->GetPlayer()->GetPosition().z };
	AreaFenceOBB.m_Pos = { Position.x,Position.y,Position.z };

	if (ps0->ColOBBs(playerOBB, AreaFenceOBB)) {
		//Collision::SetCollideOBB(true);
		PlayerControl::GetInstance()->GetPlayer()->isOldPos();
		return true;
	}
}

void AreaFence::FenceOpenCondition(bool condition)
{
	const float FenceDownSpeed = 0.1f;
	if (condition) {
		Position.y -=FenceDownSpeed;
		if (Position.y < FencePosY_Min) {
			
		}
	}
	else {
		FencePosY_Min = Position.y - 30;
	}
	Position.y = max(Position.y, FencePosY_Min);

	
}