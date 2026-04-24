#include "EnemySpawnerT.h"
#include "EnemyT.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Modules/AssetsModule.h"
#include "Core/Scene.h"
#include "Assets/Texture.h"
#include "Components/SpriteRenderer.h"
#include <iostream>
#include <string>

void EnemySpawnerT::Update(const float _delta_time)
{
    if (m_spawnedCount < m_maxEnemies)
    {
        m_timer += _delta_time;
        if (m_timer >= m_interval)
        {
            Spawn();
            m_timer = 0.0f;
            m_spawnedCount++;
        }
    }
}

void EnemySpawnerT::Spawn()
{
    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sm) return;

    Scene* currentScene = sm->GetSceneByName("TowerDefense");

    if (currentScene)
    {
        // --- LOGIQUE DE SELECTION DU TYPE ---
        int currentID = m_spawnedCount + 1;

        bool isSuperTank = (currentID % 10 == 0);
        bool isTank = (!isSuperTank && currentID % 5 == 0);
        bool isPlane = (!isSuperTank && !isTank && currentID % 7 == 0);

        std::string typeName = "Scout";
        if (isSuperTank)      typeName = "SUPER_TANK";
        else if (isTank)      typeName = "Tank";
        else if (isPlane)     typeName = "Avion";

        GameObject* enemy = currentScene->CreateGameObject("Enemy_" + typeName + "_" + std::to_string(m_spawnedCount));

        if (enemy)
        {
            enemy->SetPosition(Maths::Vector2f(32.0f, 224.0f));

            EnemyT* enemyComp = enemy->CreateComponent<EnemyT>();

            auto* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
            std::string texPath = "towerDefense_tile245.png";

            if (isSuperTank)
            {
                // MINI-BOSS :
                enemyComp->SetStats(25.0f, 25, EnemyType::BOSS);
                enemy->SetScale(Maths::Vector2f(1.2f, 1.2f));
                texPath = "scifiUnit_21.png";
                std::cout << "!!! [WARNING] UN SUPER TANK APPROCHE !!!" << std::endl;
            }
            else if (isTank)
            {
                // TANK :
                enemyComp->SetStats(50.0f, 8, EnemyType::TANK);
                enemy->SetScale(Maths::Vector2f(0.8f, 0.8f));
                texPath = "towerDefense_tile246.png";
            }
            else if (isPlane)
            {
                // AVION :
                enemyComp->SetStats(250.0f, 6, EnemyType::PLANE);
                enemy->SetScale(Maths::Vector2f(0.9f, 0.9f));
                texPath = "towerDefense_tile271.png";
                std::cout << "[ALERTE] CIBLE AERIENNE DETECTEE !" << std::endl;
            }
            else
            {
                // SCOUT :
                enemyComp->SetStats(100.0f, 3, EnemyType::SCOUT);
                enemy->SetScale(Maths::Vector2f(0.7f, 0.7f));
                texPath = "towerDefense_tile245.png";
            }

            if (assets) {
                Texture* tex = assets->GetAsset<Texture>(texPath);
                if (!tex) tex = assets->LoadAsset<Texture>(texPath);

                if (tex) {
                    enemy->CreateComponent<SpriteRenderer>(tex);
                }
            }

            std::cout << "[Spawner] Spawn: " << typeName << " (ID: " << currentID << ")" << std::endl;
        }
    }
}