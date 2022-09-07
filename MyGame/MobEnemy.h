#pragma once
#include"Object3d.h"
#include"Model.h"
#include "Enemy.h"
#include"Player.h"
#include"Texture.h"
#include"Sprite.h"

class MobEnemy :
    public Enemy
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MobEnemy();
 //   MobEnemy();
    /// <summary>
    /// デストラクタ
    /// </summary> 
    ~MobEnemy();

private:

    //オブジェクトのインスタンス
    //Object3d* MobObject = nullptr;
   
    //
public:

    Object3d* colBox;
  //  void Action(Player* player);
    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize( DebugCamera* camera)override;

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
  
    void Death()override;
    void AttackCoolTime()override;
    void FbxAnimationControl()override;
private:
    bool deadtrigger;
    bool SearchPlayerFlag = false;
    float GetDistance() { return distance; }
    //接地フラグ
    bool onGround = true;
    //落下ベクトル
    XMVECTOR fallV;
    
private:
   
    bool AttackFlag;
   bool DeathFlag;
private:
    bool nowAttack;
    float alpha=1;
public:
   // bool GetFolatc() { return folatc; }
    bool isendtime;
};

