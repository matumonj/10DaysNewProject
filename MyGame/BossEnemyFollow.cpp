#include "BossEnemyFollow.h"
#include "EnemyFollowState.h"
#include"PlayerControl.h"
#include"BossEnemyAttack.h"
#include"BossEnemyAttackCircle.h"
#include"BossEnemyAttackknock.h"
#include"BossEnemyAttackhalf.h"
#include"mHelper.h"
#include"Input.h"
#include"HalfAttack.h"
#include"CircleAttack.h"
#include"BossEnemyDeath.h"
void BossEnemyFollow::Initialize(Enemy* enmey)
{

}

void BossEnemyFollow::Update(Enemy* enemy)
{
	//索敵範囲
	const float DetectionRange = 10.0f;
	//プレイヤーが索敵範囲入ったら
	bool SearchPlayer = Collision::GetLength(enemy->GetPosition(), PlayerControl::GetInstance()->GetPlayer()->GetPosition()) < DetectionRange;

	float angleX, angleZ, dis;
	//追跡スピード
	float centerSpeed = 0.01f;

	angleX = (PlayerControl::GetInstance()->GetPlayer()->GetPosition().x - enemy->GetPosition().x);
	angleZ = (PlayerControl::GetInstance()->GetPlayer()->GetPosition().z - enemy->GetPosition().z);

	//敵とプレイヤーの距離求め
	dis = sqrtf((enemy->GetPosition().x - PlayerControl::GetInstance()->GetPlayer()->GetPosition().x) * (enemy->GetPosition().x - PlayerControl::GetInstance()->GetPlayer()->GetPosition().x)
		+ (enemy->GetPosition().z - PlayerControl::GetInstance()->GetPlayer()->GetPosition().z) * (enemy->GetPosition().z - PlayerControl::GetInstance()->GetPlayer()->GetPosition().z));


	//敵がプエレイヤーの方向く処理
	XMVECTOR positionA = { PlayerControl::GetInstance()->GetPlayer()->GetPosition().x,PlayerControl::GetInstance()->GetPlayer()->GetPosition().y, PlayerControl::GetInstance()->GetPlayer()->GetPosition().z };
	XMVECTOR positionB = { enemy->GetPosition().x,enemy->GetPosition().y,enemy->GetPosition().z };
	//プレイヤーと敵のベクトルの長さ(差)を求める
	XMVECTOR SubVector = DirectX::XMVectorSubtract(positionB, positionA);// positionA - positionB;

	//角度の取得 プレイヤーが敵の索敵位置に入ったら向きをプレイヤーの方に
	RotY = atan2f(SubVector.m128_f32[0], SubVector.m128_f32[2]);
	//移動ベクトルをy軸周りの角度で回転
	XMVECTOR move = { 0,0,0.1f,0 };

	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(enemy->GetRotation().y));

	move = XMVector3TransformNormal(move, matRot);

	enemy->SetRotation({ enemy->GetRotation().x,
		 RotY * 60 + 180,
		enemy->GetRotation().z });
	if (Collision::GetLength(enemy->GetPosition(), PlayerControl::GetInstance()->GetPlayer()->GetPosition()) > 10) {
		enemy->SetPosition({
					enemy->GetPosition().x + move.m128_f32[0],
					enemy->GetPosition().y,
					enemy->GetPosition().z + move.m128_f32[2] }
		);
	}
	
	if (Collision::GetLength(enemy->GetPosition(), PlayerControl::GetInstance()->GetPlayer()->GetPosition()) < 20) {
		if (enemy->GetCoolTime() == 0) {
			enemy->ChangeState_Boss(new BossEnemyAttack());
		}
	}


		if (Percent::GetParcent(enemy->GetMaxHP(), enemy->GetHP()) <= 80.0f) {
			HalfAttack::GetInstance()->SetAttackFase(true);
			if (enemy->GetAttack_Half_End()==false) {
				enemy->SetAttack_Half_Start(true);
			}
			else{ 
				enemy->SetAttack_Half_Start(false);
			}
			if (enemy->GetAttack_Half_Start()) {
				if (HalfAttack::GetInstance()->GetFaseEnd() != HalfAttack::FASEFOUR) {
					enemy->ChangeState_Boss(new BossEnemyAttackHalf());
				}
			}
}
		if (Percent::GetParcent(enemy->GetMaxHP(), enemy->GetHP()) <= 60.0f) {
			CircleAttack::GetInstance()->SetAttackFase(true);
			if (enemy->GetAttack_Circle_End() == false) {
				enemy->SetAttack_Circle_Start(true);
			} else {
				enemy->SetAttack_Circle_Start(false);
			}
			if (enemy->GetAttack_Circle_Start()) {
				if (CircleAttack::GetInstance()->GetFaseEnd() != CircleAttack::FASEFOUR) {
					enemy->ChangeState_Boss(new BossEnemyAttackCircle());
				}
			}
		}
		if (Percent::GetParcent(enemy->GetMaxHP(), enemy->GetHP()) <= 40.0f) {
		HalfAttack::GetInstance()->SetAttackFase(true);
		if (enemy->GetAttack_Half2_End() == false) {
			enemy->SetAttack_Half2_Start(true);
		}
		else {
			enemy->SetAttack_Half2_Start(false);
		}
		if (enemy->GetAttack_Half2_Start()) {
			if (HalfAttack::GetInstance()->GetFaseEnd() != HalfAttack::FASEFOUR) {
			enemy->ChangeState_Boss(new BossEnemyAttackHalf());
		}
	}
}
		if (enemy->GetHP() <= 0.0f) {
			enemy->ChangeState_Boss(new BossEnemyDeath());
		}
}