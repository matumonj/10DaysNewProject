#pragma once
#include "Player.h"
class Bird :
    public Player
{
public:
    void Initialize()override;

    void Update()override;

    void Draw()override;

    void IconDraw()override;

    void Attack(Sushi* sushis)override;

private:
    float CoolTime;
};

