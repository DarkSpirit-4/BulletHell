#pragma once
#include "Core/Component.h"

class LaserTrap : public Component
{
public:
    void Update(float _deltaTime) override;

private:
    float timer = 0.0f;
    float warningDuration = 1.2f;
    float activeDuration = 0.8f;
    bool isDangerouslyActive = false;
};