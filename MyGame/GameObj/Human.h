#pragma once
#include "Player.h"


class Human :public  Player {


    void Initialize()override;

    void Update()override;

    void Draw()override;

    void IconDraw()override;

    void Attack(Sushi* sushis)override;
    void Attack2(Sushi* sushis)override;
    void Attack3(Sushi* sushis)override;

private:
};