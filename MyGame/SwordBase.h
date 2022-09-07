#pragma once
#include"CollisionPrimitive.h"
#include "ObjectManager.h"
class SwordBase :
    public ObjectManager
{
public:
     SwordBase();
    virtual ~SwordBase();
public:
    virtual void Initialize(DebugCamera* camera)override;
    virtual void Update(DebugCamera* camera)override;
    virtual void Draw()override;
protected:
    float Damage;
    float CoolTime;
    Box DamageArea;
    XMFLOAT2 Radius;
public:
    float GetDamage() { return Damage; }
    float GetCoolTime() { return CoolTime; }
    Box SwordDamageArea() { return DamageArea; }
};

