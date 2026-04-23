#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include <cmath>

class Player : public Component
{
public:
    void Update(const float _delta_time) override
    {
        Maths::Vector2<float> position = GetOwner()->GetPosition();

        // --- MOUVEMENT ---
        if (InputModule::GetKey(sf::Keyboard::Key::D))
        {
            position.x += speed * _delta_time;
        }
        if (InputModule::GetKey(sf::Keyboard::Key::Q))
        {
            position.x -= speed * _delta_time;
        }
        if (InputModule::GetKey(sf::Keyboard::Key::Z))
        {
            position.y -= speed * _delta_time;
        }
        if (InputModule::GetKey(sf::Keyboard::Key::S))
        {
            position.y += speed * _delta_time;
        }

        // --- LIMITES DE L'ÉCRAN (CLAMPING) ---
        float screenWidth = 800.f;
        float screenHeight = 800.f;
        float halfW = 0.f;
        float halfH = 0.f;

        // On récupère la taille via le collider pour un blocage précis
        auto* col = GetOwner()->GetComponent<SquareCollider>();
        if (col)
        {
            halfW = col->GetWidth() / 2.f;
            halfH = col->GetHeight() / 2.f;
        }

        // Blocage X
        if (position.x < halfW) position.x = halfW;
        if (position.x > screenWidth - halfW) position.x = screenWidth - halfW;

        // Blocage Y
        if (position.y < halfH) position.y = halfH;
        if (position.y > screenHeight - halfH) position.y = screenHeight - halfH;

        GetOwner()->SetPosition(position);

        // --- ROTATION ---
        Maths::Vector2f mousePos(
            (float)InputModule::GetMousePosition().x,
            (float)InputModule::GetMousePosition().y
        );

        Maths::Vector2f direction = mousePos - position;
        float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
        angle += 90.f;

        float spriteOffset = 180.f;
        GetOwner()->SetRotation(sf::degrees(angle + spriteOffset));

        // --- QUITTER ---
        if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
        {
            Engine::GetInstance()->RequestQuit();
        }
    }

    float speed = 200.0f;
};