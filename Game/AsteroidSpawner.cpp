#include "AsteroidSpawner.h"
#include "LaserTrap.h"
#include <cstdlib> 
#include "Asteroid.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"
#include "Components/SpriteRenderer.h"
#include "Components/RectangleShapeRenderer.h" // Ajouté pour le laser
#include "SquareCollider.h"
#include "Assets/Texture.h"
#include "Modules/AssetsModule.h"

void AsteroidSpawner::Update(float dt)
{
    // --- Gestion des Timers ---
    timer += dt;
    if (canSpawnLaser) {
        laserTimer += dt;
    }

    // Récupérer la scène
    auto* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sceneModule || sceneModule->GetScenesList().empty()) return;
    Scene* scene = sceneModule->GetScenesList().front().get();

    // =========================
    // 1. SPAWN ASTÉROÏDES
    // =========================
    if (timer >= spawnRate)
    {
        timer = 0.f;
        float x = static_cast<float>(rand() % 800);
        float y = -100.f;

        GameObject* asteroid = scene->CreateGameObject("Asteroid");
        asteroid->SetPosition(Maths::Vector2f(x, y));
        asteroid->SetScale(Maths::Vector2f(0.15f, 0.15f));
        asteroid->CreateComponent<Asteroid>();

        auto* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
        Texture* texture = assets->LoadAsset<Texture>("spaceMeteors_003.png");

        if (texture)
        {
            asteroid->CreateComponent<SpriteRenderer>(texture);
            sf::Vector2u texSize = texture->GetTexture().getSize();
            Maths::Vector2f scale = asteroid->GetScale();
            auto* collider = asteroid->CreateComponent<SquareCollider>();
            collider->SetWidth(static_cast<float>(texSize.x) * scale.x * 0.8f);
            collider->SetHeight(static_cast<float>(texSize.y) * scale.y * 0.8f);
        }
    }

    // =========================
    // 2. SPAWN LASER (Seulement si autorisé)
    // =========================
    if (canSpawnLaser && laserTimer >= 4.0f)
    {
        laserTimer = 0.f;
        GameObject* laser = scene->CreateGameObject("LaserTrap");
        if (laser)
        {
            float randomY = 100.f + static_cast<float>(rand() % 500);
            laser->SetPosition(Maths::Vector2f(-100.f, randomY));

            auto* rend = laser->CreateComponent<RectangleShapeRenderer>();
            if (rend) {
                rend->SetSize(Maths::Vector2f(2000.f, 30.f));
                rend->SetColor(sf::Color(255, 0, 0, 0));
            }
            laser->CreateComponent<LaserTrap>();
        }
    }
}