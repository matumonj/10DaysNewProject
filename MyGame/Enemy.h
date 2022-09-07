#pragma once
#ifndef ENEMY_H_
#define ENMEY_H_

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <d3dx12.h>
#include <DirectXMath.h>
#include <string>
#include"DirectXCommon.h"
#include"DebugCamera.h"
#include"Input.h"
#include"Player.h"
#include"EnemyState.h"
#include"BossEnemyState.h"
#include"Texture.h"
#include"Destroy.h"
#include"ObjectManager.h"
class NodeBase;
/// <summary>
/// 敵キャラの基底クラス
/// </summary>
/// 
class Enemy :public ObjectManager
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Enemy();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~Enemy();

	static Enemy* Create(Model* model, DebugCamera* camera);

private:
	EnemyState* _state;
protected:
	float EnemyHP;
	float MaxHP;
	
	bool Alive = true;
protected:
	bool MoveFlag;
	int Number;
	bool animeflag;

	float AttackTime;
private:
	bool RecvDamagef;
	float OldHP;
	XMFLOAT3 OldPos;

protected:
	bool RecvDamageJudg;
public:

	bool GetRecvDamageJudg() { return RecvDamageJudg; }
	bool GetRecvDamage() { return RecvDamagef; }
	void SetRecvDamage(bool f) { RecvDamagef = f; }
	void SetMoveFlag(bool f) { MoveFlag = f; }
	bool GetMoveFlag() { return MoveFlag; }
	virtual bool GetDead() { if (EnemyHP <= 0) { return true; } }
	void RecvDamage(int Damage); 
	bool GetonFlag() { return onGround; }
	bool GetAlive() { return Alive; };
	float GetHP() { return EnemyHP; };
	float GetMaxHP() { return MaxHP; }
	void SetHP(float hp) { EnemyHP = hp; }
	void Setcol(XMFLOAT4 c) { m_fbxObject->SetColor(c); }

	void Turn_toPlayer();
	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize( DebugCamera* camera)override;

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update(DebugCamera* camera)override;

	virtual void Death()=0;

	virtual void FbxAnimationControl() = 0;
	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw()override;

	virtual void Action();
	void EnemyPop(int HP);
	void SetStartPosition(XMFLOAT3 position) {
		StartPosition = { 0,0,0}; }
	/// <summary>
	/// 解放処理
	/// </summary>
	virtual void Finalize();

	float distance;
	bool AfterAttack;
	float GetDistance() { return distance; }

	void Getposition(float* x, float* y, float* z) {
		*x = this->Position.x;
		*y = this->Position.y;
		*z = this->Position.z;
	};

	XMFLOAT3 GetScale() { return Scale; }

	void SetScale(XMFLOAT3 scale) { Scale = scale; }

	bool GetDeathTime() { return DeathFlag; }
	void SetDeathTime(bool f) { if (!DeathFlag) { DeathFlag = f; } }
	int GetTime() { return time; }

	virtual void AttackCoolTime()=0;
	int GetAttackCoolTime() { return cooltime; }
	bool f_AttackFlag;
	void SetAttackTime(bool f) { if (f_time < AttackTime) { f_AttackFlag = f; } }
	bool GetAttackTime() { return f_AttackFlag; }
protected:
	bool nowDeath;
	int cooltime=0;
	
	int onGroundTime = 0;
	int time=0;
protected:
	float f_time;
	float start_time;
	float end_time;
	float DeathTime;
	XMFLOAT3 StartPosition;
	int PopCount;

	protected:

	bool DeathFlag;
protected:
	public:
		enum EnemyStates {
			ALIVE,
			None,
			DEAD,
			AFTER_ATTACK,
			NOW_ATTACK
		};
		struct Attack_SE {
			bool start;
			bool end;
		};
		Attack_SE Attack_Circle;
		Attack_SE Attack_Knock;
		Attack_SE Attack_Half;
		Attack_SE Attack_Half2;

		bool GetAttack_Half_Start() { return Attack_Half.start; }
		bool GetAttack_Half2_Start() { return Attack_Half2.start; }
		bool GetAttack_Half_End() { return Attack_Half.end; }
		bool GetAttack_Half2_End() { return Attack_Half2.end; }
		bool GetAttack_Circle_Start() { return Attack_Circle.start; }
		bool GetAttack_Circle_End() { return Attack_Circle.end; }

		void SetAttack_Half_Start(bool f) {Attack_Half.start=f; }
		void SetAttack_Half2_Start(bool f) {  Attack_Half2.start = f; }
		void SetAttack_Circle_Start(bool f) { Attack_Circle.start = f; }
		void SetAttack_Circle_End(bool f) { Attack_Circle.end = f; }
		void SetAttack_Half_End(bool f) {  Attack_Half.end = f; }
		void SetAttack_Half2_End(bool f) { Attack_Half2.end = f; }

		EnemyStates GetState() { return state; }
		bool GetNowDeath() { return nowDeath; }
		int GetCoolTime() { return cooltime; }
protected:
		EnemyStates state=None;
	
	public:
		void ChangeState_Mob(EnemyState* state);
		void ChangeState_Boss(BossEnemyState* state);
protected:
	EnemyState* state_mob;
	BossEnemyState* state_boss;
};


#endif