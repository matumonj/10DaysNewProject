#pragma once
#include "Sushi.h"
class Tuna :
    public Sushi
{
public:

    void Initialize()override;

    void Update()override;

    void Draw()override;

private:
    POINT p;
    float x, y;
    float mx, my, mz;
    XMVECTOR Pos3d;
};

