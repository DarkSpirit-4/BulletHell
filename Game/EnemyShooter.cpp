#include "EnemyShooter.h"
#include "Bullet.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Components/RectangleShapeRenderer.h"
#include "Components/SquareCollider.h"

void EnemyShooter::Update(float deltaTime) {
    timer += deltaTime;

    float currentDelay = (shotsFired < maxShots) ? burstRate : cooldownRate;

    if (timer >= currentDelay) {
        if (shotsFired < maxShots) {
            auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
            Scene* scene = sm->GetScenesList().front().get();

            // 1. TROUVER LE JOUEUR POUR VISER
            GameObject* player = scene->FindGameObject("Player");
            Maths::Vector2f fireDir(0.0f, 1.0f); // Direction par défaut (bas)

            if (player) {
                // Vecteur = Cible - Origine
                Maths::Vector2f playerPos = player->GetPosition();
                Maths::Vector2f myPos = GetOwner()->GetPosition();

                fireDir = playerPos - myPos;
                float distance = fireDir.Magnitude();

                if (distance > 0.1f) {
                    fireDir = fireDir / distance; // Normalisation
                }
            }

            // 2. CRÉATION DE LA BALLE
            GameObject* bullet = scene->CreateGameObject("EnemyBullet");
            if (bullet) {
                bullet->SetPosition(GetOwner()->GetPosition());

                Bullet* b = bullet->CreateComponent<Bullet>();
                if (b) {
                    b->direction = fireDir; // On utilise la direction calculée vers le joueur
                    b->speed = 250.0f;      // Un peu plus rapide car c'est un tir visé
                    b->isEnemy = true;
                }

                // Visuel et Hitbox
                auto* rend = bullet->CreateComponent<RectangleShapeRenderer>();
                if (rend) {
                    rend->SetColor(sf::Color::Cyan);
                    rend->SetSize(Maths::Vector2f(8.f, 8.f));
                }
                auto* col = bullet->CreateComponent<SquareCollider>();
                if (col) {
                    col->SetWidth(8.0f);
                    col->SetHeight(8.0f);
                }
            }
            shotsFired++;
        }
        else {
            shotsFired = 0;
        }
        timer = 0.0f;
    }
}