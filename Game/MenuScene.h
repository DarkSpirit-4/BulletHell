#pragma once

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "MainMenu.h"

class MenuScene final : public Scene
{
public:
    // On garde "true" car c'est la SEULE scène qui doit être active au début
    MenuScene() : Scene("MenuScene", true)
    {
        GameObject* menuManager = CreateGameObject("MenuManager");
        if (menuManager)
        {
            menuManager->CreateComponent<MainMenu>();
        }
    }
};