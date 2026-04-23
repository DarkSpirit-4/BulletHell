#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

class Enemy : public Component
{
public:
    void Update(float _deltaTime) override;

    Maths::Vector2f direction;
    float speed = 100.0f;
};