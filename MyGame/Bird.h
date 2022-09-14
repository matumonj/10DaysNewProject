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

    void Attack(std::vector<Sushi*>  sushis)override;
    void Attack2(std::vector<Sushi*>  sushis)override;
     void Attack3(std::vector<Sushi*> sushis)override;
private:
    float CoolTime;
};

