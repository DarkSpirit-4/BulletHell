#include "Bullet.h"
#include "Health.h"
#include "Components/SquareCollider.h" 
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h" // Ajouté pour accéder à DestroyGameObject

void Bullet::Update(float deltaTime) {
    GameObject* owner = GetOwner();
    if (!owner) return;

    // 1. Déplacement
    owner->SetPosition(owner->GetPosition() + (direction * speed * deltaTime));

    // 2. Récupération des modules et de la scène
    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sm) return;

    Scene* scene = sm->GetSceneByName("BulletHell");
    if (!scene) return;

    auto* myCollider = owner->GetComponent<SquareCollider>();
    if (!myCollider) return;

    // 3. Détection de collision
    if (this->isEnemy) {
        // --- LOGIQUE DE LA PLUIE (Ennemis -> Joueur) ---
        GameObject* player = scene->FindGameObject("Player");
        if (player) {
            auto* playerCol = player->GetComponent<SquareCollider>();
            if (playerCol && SquareCollider::IsColliding(*myCollider, *playerCol)) {
                auto* h = player->GetComponent<Health>();
                if (h) h->TakeDamage(1);

                // Destruction explicite via la scène
                scene->DestroyGameObject(owner);
                return;
            }
        }
    }
    else {
        // --- LOGIQUE DES TIRS DU JOUEUR (Joueur -> Ennemis) ---
        for (const auto& obj : scene->GetGameObjects()) {

            if (obj->GetName() != "Enemy" || obj.get() == owner) continue;

            auto* targetCol = obj->GetComponent<SquareCollider>();
            if (targetCol && SquareCollider::IsColliding(*myCollider, *targetCol)) {

                auto* h = obj->GetComponent<Health>();
                if (h) {
                    h->TakeDamage(1);
                    Logger::Log(ELogLevel::Debug, "Impact! Vie de l'ennemi : {}", h->currentHealth);
                }

                // Destruction explicite via la scène
                scene->DestroyGameObject(owner);
                return;
            }
        }
    }

    // 4. Auto-destruction (Si la balle ne touche rien après 5s)
    lifetime += deltaTime;
    if (lifetime > 5.0f) {
        scene->DestroyGameObject(owner);
        return;
    }
}