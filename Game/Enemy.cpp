#include "Enemy.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"

void Enemy::Update(float _deltaTime)
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    // 1. Déplacement en ligne droite
    Maths::Vector2f pos = owner->GetPosition();
    pos.x += direction.x * speed * _deltaTime;
    pos.y += direction.y * speed * _deltaTime;
    owner->SetPosition(pos);

    // 2. Vérification des limites de l'écran (800x800 + marges)
    if (pos.x < -150 || pos.x > 950 || pos.y < -150 || pos.y > 950)
    {
        // 3. RÉCUPÉRATION DE L'AUTORITÉ DE LA SCÈNE
        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        if (sm)
        {
            Scene* scene = sm->GetSceneByName("BulletHell");
            if (scene)
            {
                // On demande explicitement à la scène de supprimer l'objet
                scene->DestroyGameObject(owner);
                return; // On arrête l'Update ici
            }
        }

        // Sécurité si le SceneModule ou la scène sont introuvables
        owner->Destroy();
    }
}