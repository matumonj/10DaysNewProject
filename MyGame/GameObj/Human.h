#pragma once
#include "Player.h"


class Human :public  Player {


    void Initialize()override;

    void Update()override;

    void Draw()override;

    void IconDraw()override;

    void Attack(Sushi* sushis)override;


private:
};