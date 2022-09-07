#include "Enemy.h"
#include"mHelper.h"
#include"EnemyWalkState.h"
#include"EnemyAttackState.h"
#include"EnemyStayState.h"
#include"EnemyFollowState.h"
#include"Collision.h"
#include"mHelper.h"
#include"SphereCollider.h"
#include"CollisionManager.h"
#include"CollisionAttribute.h"
#include"imgui.h"
#include"SceneManager.h"
#include"EnemyFollowState.h"
#include"BossEnemyFollow.h"
using namespace DirectX;
Enemy::Enemy()
{

	state_boss= new BossEnemyFollow();
	state_mob = new EnemyWalkState();
}

Enemy::~Enemy()
{
	delete _state, state_mob;
}


//‰Šú‰»ˆ—
void Enemy::Initialize(DebugCamera* camera)
{

}

//XVˆ—
void Enemy::Update(DebugCamera* camera)
{
}


void Enemy::Action()
{
	AttackCoolTime();
}
void Enemy::RecvDamage(int Damage) 
{
	RecvDamageJudg = true;
	EnemyHP = EnemyHP - Damage;
}
void Enemy::EnemyPop(int HP)
{
	

}
//•`‰æˆ—
void Enemy::Draw()
{
}

//‰ğ•úˆ—
void Enemy::Finalize()
{
}



void Enemy::Turn_toPlayer()
{
	
}

void Enemy::ChangeState_Mob(EnemyState* state)
{
	delete state_mob;
	state_mob = state;
}

void Enemy::ChangeState_Boss(BossEnemyState* state)
{
	delete state_boss;
	state_boss = state;
}