#pragma once
#include "Core/Component.h"
#include <vector>

class GameObject;

class HealthBar : public Component
{
public:
    void Start() override;
    void Update(float dt) override;

private:
    std::vector<GameObject*> hearts;
    int lastHp = 5;
};