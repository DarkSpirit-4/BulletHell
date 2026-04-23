#pragma once

#include "Player.h"
#include "Shooter.h"
#include "Health.h"
#include "GameManager.h"

#include "Assets/Texture.h"
#include "Components/SpriteRenderer.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Modules/AssetsModule.h"
#include "SquareCollider.h"

#include "AsteroidSpawner.h"

class DefaultScene final : public Scene
{
public:
    DefaultScene() : Scene("DefaultScene")
    {

        // GAME MANAGER (PHASES)
        // =========================
        GameObject* manager = CreateGameObject("GameManager");
        manager->CreateComponent<GameManager>();


        // PHASE 1 : ASTEROÏDES
        // =========================
        GameObject* spawner = CreateGameObject("Spawner");
        spawner->CreateComponent<AsteroidSpawner>();

        // PLAYER
        // =========================
        GameObject* player = CreateGameObject("Player");
        player->SetPosition(Maths::Vector2f(400.f, 400.f));
        player->SetScale(Maths::Vector2f(0.7f, 0.7f));

        // Collider
        auto* playerCol = player->CreateComponent<SquareCollider>();
        playerCol->SetWidth(40.0f);
        playerCol->SetHeight(40.0f);

        // Composants gameplay
        player->CreateComponent<Player>();
        player->CreateComponent<Shooter>(); // ok de le laisser

        // Vie
        auto* hp = player->CreateComponent<Health>();
        if (hp) hp->currentHealth = 5;


        // SPRITE
        // =========================
        AssetsModule* assets = Engine::GetInstance()
            ->GetModuleManager()
            ->GetModule<AssetsModule>();

        Texture* playerTexture = assets->LoadAsset<Texture>("enemyRed5.png");

        if (playerTexture)
        {
            player->CreateComponent<SpriteRenderer>(playerTexture);
        }
    }
};