#include "BulletHellSpawner.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyShooter.h"
#include "Health.h"
#include "LaserTrap.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Modules/AssetsModule.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/SpriteRenderer.h"
#include "Components/RectangleShapeRenderer.h"
#include "SquareCollider.h"
#include <cmath>

void BulletHellSpawner::Update(float _deltaTime)
{
    // Mise à jour des timers
    bulletTimer += _deltaTime;
    enemyTimer += _deltaTime;
    laserTimer += _deltaTime;

    // Rotation de la ligne de spawn orbitale
    angleTimer += _deltaTime * 4.0f;

    // 1. SPAWN DES BALLES ORBITALES
    if (bulletTimer >= bulletRate)
    {
        bulletTimer = 0.0f;
        SpawnRainBullet();
    }

    // 2. SPAWN DES ENNEMIS
    if (enemyTimer >= enemyRate)
    {
        enemyTimer = 0.0f;
        SpawnEnemy();
    }

    // 3. SPAWN DU LASER (Séquence 4)
    if (canSpawnLaser)
    {
    if (laserTimer >= 6.0f) // Un laser toutes les 6 secondes
    {
        laserTimer = 0.0f;

        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        Scene* scene = sm->GetScenesList().front().get();

        if (scene)
        {
            GameObject* laser = scene->CreateGameObject("LaserTrap");
            if (laser)
            {
                // Hauteur aléatoire
                float randomY = 100.f + static_cast<float>(rand() % 700);

                // Positionné à gauche (-100) avec une largeur de 2000 pour tout couvrir
                laser->SetPosition(Maths::Vector2f(-100.f, randomY));

                auto* rend = laser->CreateComponent<RectangleShapeRenderer>();
                if (rend) {
                    rend->SetSize(Maths::Vector2f(2000.f, 50.f));
                    rend->SetColor(sf::Color(255, 0, 0, 0)); // Transparent au début
                }

                laser->CreateComponent<LaserTrap>();
                }
            }
        }
    }
}

void BulletHellSpawner::SpawnRainBullet()
{
    auto* mm = Engine::GetInstance()->GetModuleManager();
    Scene* scene = mm->GetModule<SceneModule>()->GetScenesList().front().get();

    GameObject* rain = scene->CreateGameObject("RainBullet");
    if (rain)
    {
        float centerX = 400.0f;
        float centerY = 400.0f;
        float radius = 450.0f;
        float rowWidth = 800.0f;

        // Logique orbitale
        float rowCenterX = centerX + std::cos(angleTimer) * radius;
        float rowCenterY = centerY + std::sin(angleTimer) * radius;

        float perpX = -std::sin(angleTimer);
        float perpY = std::cos(angleTimer);

        float randomOffset = ((float)(rand() % 100) / 100.0f - 0.5f) * rowWidth;

        float finalPosX = rowCenterX + (perpX * randomOffset);
        float finalPosY = rowCenterY + (perpY * randomOffset);

        rain->SetPosition(Maths::Vector2f(finalPosX, finalPosY));

        // Direction vers le centre
        float diffX = centerX - finalPosX;
        float diffY = centerY - finalPosY;
        float mag = std::sqrt(diffX * diffX + diffY * diffY);

        Maths::Vector2f dir(0.f, 0.f);
        if (mag != 0) {
            dir.x = diffX / mag;
            dir.y = diffY / mag;
        }

        Bullet* b = rain->CreateComponent<Bullet>();
        if (b) {
            b->direction = dir;
            b->speed = 200.0f;
            b->isEnemy = true;
        }

        auto* renderer = rain->CreateComponent<RectangleShapeRenderer>();
        if (renderer) {
            renderer->SetSize(Maths::Vector2f(10.f, 10.f));
            renderer->SetColor(sf::Color::Red);
        }

        auto* col = rain->CreateComponent<SquareCollider>();
        if (col) {
            col->SetWidth(10.f);
            col->SetHeight(10.f);
        }
    }
}

void BulletHellSpawner::SpawnEnemy()
{
    auto* mm = Engine::GetInstance()->GetModuleManager();
    Scene* scene = mm->GetModule<SceneModule>()->GetScenesList().front().get();
    auto* assets = mm->GetModule<AssetsModule>();

    GameObject* enemyObj = scene->CreateGameObject("Enemy");
    if (enemyObj)
    {
        enemyObj->SetScale(Maths::Vector2f(0.3f, 0.3f));

        float startX, startY;
        Maths::Vector2f dir(0.f, 0.f);
        int side = rand() % 3;
        switch (side) {
        case 0: startX = (float)(rand() % 600); startY = -60.f; dir = Maths::Vector2f(0.f, 1.f); break;
        case 1: startX = -60.f; startY = (float)(rand() % 600); dir = Maths::Vector2f(1.f, 0.f); break;
        case 2: startX = 860.f; startY = (float)(rand() % 600); dir = Maths::Vector2f(-1.f, 0.f); break;
        }

        enemyObj->SetPosition(Maths::Vector2f(startX, startY));

        Texture* tex = assets->LoadAsset<Texture>("spaceStation_029.png");
        if (tex) {
            enemyObj->CreateComponent<SpriteRenderer>(tex);
            auto* col = enemyObj->CreateComponent<SquareCollider>();
            if (col) {
                sf::Vector2u size = tex->GetTexture().getSize();
                col->SetWidth(static_cast<float>(size.x) * 0.3f);
                col->SetHeight(static_cast<float>(size.y) * 0.3f);
            }
        }

        Enemy* e = enemyObj->CreateComponent<Enemy>();
        if (e) { e->direction = dir; e->speed = 80.0f; }

        enemyObj->CreateComponent<Health>()->currentHealth = 3;
        enemyObj->CreateComponent<EnemyShooter>();
    }
}