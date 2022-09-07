#pragma once
#include "SwordBase.h"
class NormalSword :
    public SwordBase
{
public:
    ~NormalSword();
public:
    void Initialize(DebugCamera* camera)override;
    void Update(DebugCamera* camera)override;
    void Draw()override;
};

