#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"Player.h"
#include"Texture.h"
#include"Sprite.h"
class BossEnemy :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BossEnemy();
   // BossEnemy();
    /// <summary>
    /// デストラクタ
    /// </summary> 
    ~BossEnemy();

private:

    Enemy* mob;
    //オブジェクトのインスタンス
    Object3d* MobObject = nullptr;
    //モデルのインスタンス
    Model* MobModel = nullptr;
    //
    Texture* SearchPlayerTexture = nullptr;
public:
    //  void Action(Player* player);
      /// <summary>
      /// 初期化
      /// </summary>
    void Initialize(DebugCamera* camera)override;

    /// <summary>
    /// 更新処理
    /// </summary>
    void Update(DebugCamera* camera)override;

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// 解放処理
    /// </summary>
    void Finalize()override;
   
    void AttackCoolTime()override;
    void FbxAnimationControl()override;
    
    void Death()override;
private:
    float GetDistance() { return distance; }
    //接地フラグ
    bool onGround = true;
    //落下ベクトル
    XMVECTOR fallV;
public:
    void FieldCollision(DebugCamera* camera);

    bool DeathFlag;
private:
    bool nowAttack;
    bool nowDeath;
    float defaulttime = 1.8;
};

