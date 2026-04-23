#include "Bullet.h"
#include "Health.h"
#include "Components/SquareCollider.h" 
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"

void Bullet::Update(float deltaTime) {
    GameObject* owner = GetOwner();
    if (!owner) return;

    // 1. Déplacement
    owner->SetPosition(owner->GetPosition() + (direction * speed * deltaTime));

    // 2. Récupération du Collider de la balle
    auto* myCollider = owner->GetComponent<SquareCollider>();
    if (!myCollider) return;

    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sm || sm->GetScenesList().empty()) return;
    Scene* scene = sm->GetScenesList().front().get();

    // 3. Détection de collision
    if (this->isEnemy) {
        // --- LOGIQUE DE LA PLUIE (Ennemis -> Joueur) ---
        GameObject* player = scene->FindGameObject("Player");
        if (player) {
            auto* playerCol = player->GetComponent<SquareCollider>();
            if (playerCol && SquareCollider::IsColliding(*myCollider, *playerCol)) {
                auto* h = player->GetComponent<Health>();
                if (h) h->TakeDamage(1);
                owner->Destroy();
                return;
            }
        }
    }
    else {
        // --- LOGIQUE DES TIRS DU JOUEUR (Joueur -> Ennemis) ---
        for (const auto& obj : scene->GetGameObjects()) {

            // FILTRE : On ignore tout ce qui n'est pas un "Enemy"
            if (obj->GetName() != "Enemy" || obj.get() == owner) continue;

            auto* targetCol = obj->GetComponent<SquareCollider>();
            if (targetCol) {
                // Vérification physique de l'intersection
                if (SquareCollider::IsColliding(*myCollider, *targetCol)) {

                    // LOG DE DEBUG : Apparaîtra dans ta console au moment de l'impact
                    Logger::Log(ELogLevel::Info, "Collision : Balle du joueur a touche un Enemy !");

                    auto* h = obj->GetComponent<Health>();
                    if (h) {
                        h->TakeDamage(1);
                        Logger::Log(ELogLevel::Debug, "Vie de l'ennemi : {}", h->currentHealth);
                    }

                    // Destruction de la balle
                    owner->Destroy();
                    return;
                }
            }
        }
    }

    // 4. Auto-destruction (Si la balle ne touche rien)
    lifetime += deltaTime;
    if (lifetime > 5.0f) {
        owner->Destroy();
    }
}