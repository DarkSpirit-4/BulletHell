#include "GameManager.h"
#include <iostream>
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"

// Spawners
#include "AsteroidSpawner.h"
#include "BulletHellSpawner.h"

void GameManager::Update(float dt)
{
    timer += dt;

    // Séquence 1 (Astéroïdes) -> Séquence 2 (Bullet Hell) après 20s
    if (currentPhase == GamePhase::Asteroids1 && timer >= 20.f)
    {
        SwitchPhase(GamePhase::BulletHell1);
    }
    // Séquence 2 (Bullet Hell) -> Séquence 3 (Astéroïdes + Laser) après 20s
    else if (currentPhase == GamePhase::BulletHell1 && timer >= 20.f)
    {
        SwitchPhase(GamePhase::Asteroids2);
    }
    // Séquence 3 (Astéroïdes + Laser) -> Séquence 4 (Bullet Hell + Laser) après 20s
    else if (currentPhase == GamePhase::Asteroids2 && timer >= 20.f)
    {
        SwitchPhase(GamePhase::BulletHell2);
    }
}

void GameManager::SwitchPhase(GamePhase newPhase)
{
    currentPhase = newPhase;
    timer = 0.f;

    std::cout << "--- CHANGEMENT DE PHASE : " << (int)newPhase << " ---" << std::endl;

    SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sceneModule || sceneModule->GetScenesList().empty()) return;
    Scene* scene = sceneModule->GetScenesList().front().get();

    // 1. Nettoyage de l'ancien spawner pour éviter les conflits
    for (const auto& obj : scene->GetGameObjects())
    {
        if (obj->GetName() == "Spawner")
        {
            obj->Destroy();
        }
    }

    // 2. Création du nouveau spawner
    GameObject* spawner = scene->CreateGameObject("Spawner");
    if (!spawner) return;

    // --- LOGIQUE ASTÉROÏDES (Phases 1 et 3) ---
    if (newPhase == GamePhase::Asteroids1 || newPhase == GamePhase::Asteroids2)
    {
        auto* script = spawner->CreateComponent<AsteroidSpawner>();

        if (newPhase == GamePhase::Asteroids2) {
            std::cout << "Action: Asteroids + LASERS Active" << std::endl;
            script->canSpawnLaser = true;
        }
        else {
            std::cout << "Action: Asteroids Only" << std::endl;
            script->canSpawnLaser = false;
        }
    }
    // --- LOGIQUE BULLET HELL (Phases 2 et 4) ---
    else if (newPhase == GamePhase::BulletHell1 || newPhase == GamePhase::BulletHell2)
    {
        auto* script = spawner->CreateComponent<BulletHellSpawner>();

        if (newPhase == GamePhase::BulletHell2) {
            std::cout << "Action: Bullet Hell + LASERS Active" << std::endl;
            script->canSpawnLaser = true; // Assure-toi d'avoir ajouté ce booléen dans BulletHellSpawner.h aussi !
        }
        else {
            std::cout << "Action: Bullet Hell Only" << std::endl;
            script->canSpawnLaser = false;
        }
    }
}