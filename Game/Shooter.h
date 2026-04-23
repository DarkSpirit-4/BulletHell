#pragma once

#include "Core/Component.h"
#include "InputModule.h"
#include "Maths/Vector2.h"

class Shooter : public Component
{
public:

    void Update(float deltaTime) override;

    // Paramètres de l'arme
    float fireRate = 0.23f;
    float timer = 0.0f;
};