#include "Asteroid.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "Health.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"

void Asteroid::Update(float dt)
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    // 1. Déplacement
    auto pos = owner->GetPosition();
    pos.y += speed * dt;
    owner->SetPosition(pos);

    // 2. Récupération sécurisée de la scène
    auto* mm = Engine::GetInstance()->GetModuleManager();
    auto* sceneModule = mm->GetModule<SceneModule>();
    if (!sceneModule) return;

    Scene* scene = sceneModule->GetSceneByName("BulletHell");
    if (!scene) return;

    // 3. Collision avec le joueur
    GameObject* player = scene->FindGameObject("Player");
    if (player)
    {
        auto* playerCol = player->GetComponent<SquareCollider>();
        auto* myCol = owner->GetComponent<SquareCollider>();

        if (playerCol && myCol && SquareCollider::IsColliding(*myCol, *playerCol))
        {
            auto* hp = player->GetComponent<Health>();
            if (hp) hp->TakeDamage(1);

            // CORRECTION : Destruction via l'autorité de la scène
            scene->DestroyGameObject(owner);
            return;
        }
    }

    // 4. Destruction si hors écran
    if (pos.y > 1000.f)
    {
        // CORRECTION : Destruction via l'autorité de la scène
        scene->DestroyGameObject(owner);
        return;
    }
}