#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

class EnemyShooter : public Component {
public:
    void Update(float deltaTime) override;

private:
    float timer = 0.0f;
    int shotsFired = 0;

    const float burstRate = 0.2f;
    const float cooldownRate = 2.5f;
    const int maxShots = 3;
};