#pragma once
#include "Sushi.h"
class Samon :
    public Sushi
{
public:

    void Initialize()override;

    void Update()override;
    void TitleUpda()override;

    void Draw()override;

private:
    POINT p;
    float x, y;
    float mx, my, mz;
    XMVECTOR Pos3d;
};

