#pragma once
#include "Core/Component.h"

class Health : public Component
{
public:
    void Update(float _deltaTime) override;
    void TakeDamage(int _amount);

    int currentHealth = 5;
    float invulnerabilityDuration = 1.5f;

private:
    float invulnerabilityTimer = 0.0f;
    bool isInvulnerable = false;
};