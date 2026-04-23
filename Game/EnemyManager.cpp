//#include "EnemyManager.h"
//#include "Enemy.h"
//#include "Health.h"
//#include "EnemyShooter.h"  // <--- AJOUT DE L'INCLUDE
//#include "Core/GameObject.h"
//#include "Core/Scene.h"
//#include "Engine.h"
//#include "Modules/AssetsModule.h"
//#include "Modules/SceneModule.h"
//#include "Components/SpriteRenderer.h"
//#include "SquareCollider.h"
//
//void EnemyManager::Update(float _deltaTime)
//{
//    spawnTimer += _deltaTime;
//
//    if (spawnTimer >= timeBetweenSpawns)
//    {
//        spawnTimer = 0.0f;
//        SpawnEnemy();
//    }
//}
//
//void EnemyManager::SpawnEnemy()
//{
//    auto* mm = Engine::GetInstance()->GetModuleManager();
//
//    auto* sm = mm->GetModule<SceneModule>();
//    if (!sm || sm->GetScenesList().empty()) return;
//
//    Scene* scene = sm->GetScenesList().front().get();
//    auto* assets = mm->GetModule<AssetsModule>();
//    if (!scene || !assets) return;
//
//    GameObject* enemyObj = scene->CreateGameObject("Enemy");
//    if (enemyObj)
//    {
//        enemyObj->SetScale(Maths::Vector2f(0.3f, 0.3f));
//
//        float startX, startY;
//        Maths::Vector2f dir(0.f, 0.f);
//
//        int side = rand() % 3;
//        switch (side)
//        {
//        case 0: startX = (float)(rand() % 700); startY = -60.f; dir = Maths::Vector2f(0.f, 1.f); break;
//        case 1: startX = -60.f; startY = (float)(rand() % 700); dir = Maths::Vector2f(1.f, 0.f); break;
//        case 2: startX = 860.f; startY = (float)(rand() % 700); dir = Maths::Vector2f(-1.f, 0.f); break;
//        }
//
//        enemyObj->SetPosition(Maths::Vector2f(startX, startY));
//
//        Texture* tex = assets->LoadAsset<Texture>("spaceStation_029.png");
//        if (tex)
//        {
//            enemyObj->CreateComponent<SpriteRenderer>(tex);
//            auto* col = enemyObj->CreateComponent<SquareCollider>();
//            if (col)
//            {
//                sf::Vector2u size = tex->GetTexture().getSize();
//                // Hitbox basée sur l'échelle 0.3f définie plus haut
//                col->SetWidth(static_cast<float>(size.x) * 0.3f);
//                col->SetHeight(static_cast<float>(size.y) * 0.3f);
//            }
//        }
//
//        // --- LOGIQUE DE MOUVEMENT ---
//        Enemy* e = enemyObj->CreateComponent<Enemy>();
//        if (e) { e->direction = dir; e->speed = 80.0f; }
//
//        // --- LOGIQUE DE SANTÉ ---
//        Health* h = enemyObj->CreateComponent<Health>();
//        if (h) h->currentHealth = 3;
//
//        // --- LOGIQUE DE TIR (Salve de 3 + Cooldown 2s) ---
//        // On l'ajoute simplement ici, le composant gère ses propres timers
//        enemyObj->CreateComponent<EnemyShooter>();
//    }
//}