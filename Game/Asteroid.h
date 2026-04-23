#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

class Asteroid : public Component
{
public:
    float speed = 350.f;

    void Update(float dt) override;
};