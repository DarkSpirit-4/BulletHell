#pragma once

#include "Core/Component.h"
#include <SFML/Graphics.hpp>

class Texture;

class MapRenderer : public Component
{
public:
    MapRenderer() = default;
    virtual ~MapRenderer() = default;

    void Awake() override;
    void Render(sf::RenderWindow* _window) override;

private:
    // Pointers vers les textures du moteur
    Texture* m_grassTex = nullptr;
    Texture* m_pathTex = nullptr;
    Texture* m_baseTex = nullptr;
};