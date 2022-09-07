#pragma once
#include "SwordBase.h"
class SmallSword :
    public SwordBase
{
public:
    ~SmallSword();
public:
    void Initialize(DebugCamera* camera)override;
    void Update(DebugCamera* camera)override;
    void Draw()override;
};

