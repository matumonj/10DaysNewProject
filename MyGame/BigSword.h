#pragma once
#include "SwordBase.h"
class BigSword :
    public SwordBase
{
public:
    ~BigSword();
public:
    void Initialize(DebugCamera* camera)override;
    void Update(DebugCamera* camera)override;
    void Draw()override;

};

