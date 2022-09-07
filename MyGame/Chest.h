#pragma once
#include "ObjectManager.h"
class Chest :
    public ObjectManager
{
public:
    Chest() {};
  //  ~Chest();

public:
    void Initialize(DebugCamera* camera)override;
    void Update(DebugCamera* camera)override;
    void Draw()override;
    bool CollideChest();
};

