#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

class Bullet : public Component {
public:
    // Ces variables sont configurées par Shooter.cpp ou BulletManager.cpp
    Maths::Vector2f direction;
    float speed = 250.0f;
    bool isEnemy = false;

    void Update(float deltaTime) override;

private:
    float lifetime = 0.0f;
    const float maxLifetime = 5.0f;
};