//#include "EnemyManager.h" // Rappel : ton .h s'appelait EnemyManager.h d'après ton message
//#include "BulletManager.h"
//#include "Bullet.h"
//#include "Engine.h"
//#include "Modules/SceneModule.h"
//#include "Core/Scene.h"
//#include "Core/GameObject.h"
//#include "Components/RectangleShapeRenderer.h"
//#include "SquareCollider.h"
//#include <cmath>
//
//void BulletManager::Update(float _deltaTime)
//{
//    spawnTimer += _deltaTime;
//    angle += _deltaTime; // Utilisation de la variable angle pour l'oscillation
//
//    if (spawnTimer >= spawnRate)
//    {
//        spawnTimer = 0.0f;
//
//        auto* mm = Engine::GetInstance()->GetModuleManager();
//        auto* sm = mm->GetModule<SceneModule>();
//        if (!sm || sm->GetScenesList().empty()) return;
//
//        Scene* scene = sm->GetScenesList().front().get();
//
//        // Création de la balle de pluie
//        GameObject* rainBullet = scene->CreateGameObject("RainBullet");
//        if (rainBullet)
//        {
//            // Position aléatoire en haut de l'écran
//            float posX = static_cast<float>(rand() % 800);
//            rainBullet->SetPosition(Maths::Vector2f(posX, -20.f));
//
//            // Configuration du composant Bullet
//            Bullet* b = rainBullet->CreateComponent<Bullet>();
//            if (b)
//            {
//                // Calcul de l'effet de balayage (Bullet Hell)
//                // On utilise sin() pour faire varier la direction X entre -0.5 et 0.5
//                float dirX = std::sin(angle * 2.0f) * 0.5f;
//
//                b->direction = Maths::Vector2f(dirX, 1.0f); // On force le type pour éviter l'ambiguïté
//                b->speed = 300.f;
//                b->isEnemy = true;
//            }
//
//            // Rendu visuel (petit rectangle Cyan)
//            auto* rend = rainBullet->CreateComponent<RectangleShapeRenderer>();
//            if (rend)
//            {
//                rend->SetColor(sf::Color::Cyan);
//                rend->SetSize(Maths::Vector2f(4.f, 12.f));
//            }
//
//            // Hitbox
//            auto* col = rainBullet->CreateComponent<SquareCollider>();
//            if (col)
//            {
//                col->SetWidth(4.f);
//                col->SetHeight(12.f);
//            }
//        }
//    }
//}