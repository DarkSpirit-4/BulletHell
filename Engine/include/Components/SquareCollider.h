#pragma once

#include "../Core/Component.h"

class SquareCollider : public Component
{
public:
    SquareCollider() = default;
    ~SquareCollider() override = default;

    float width = 1.0f;
    float height = 1.0f;

    float GetWidth() const
    {
        return width;
    }

    float GetHeight() const
    {
        return height;
    }

    void SetWidth(const float _width)
    {
        width = _width;
    }

    void SetHeight(const float _height)
    {
        height = _height;
    }

    void DebugRender(sf::RenderWindow* _window); //ajout

    static bool IsColliding(const SquareCollider& _collider_a, const SquareCollider& _collider_b);
};
