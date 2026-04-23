#pragma once

#include "Core/Component.h"

class BulletHellSpawner : public Component
{
public:
    bool canSpawnLaser = false; // Par défaut, pas de laser
    // Appelé à chaque frame par le moteur
    void Update(float _deltaTime) override;

private:
    // Fonctions internes pour organiser le code
    void SpawnRainBullet();
    void SpawnEnemy();

    // Chronomètres pour les fréquences d'apparition
    float bulletTimer = 0.0f;
    float enemyTimer = 0.0f;
    float laserTimer = 0.0f;

    // Cette variable sert à calculer la rotation de la ligne de spawn
    // Elle remplace le "angle" que tu avais dans ton BulletManager
    float angleTimer = 0.0f;

    // Paramètres de difficulté (tu peux les ajuster ici)
    const float bulletRate = 0.22f; // Une balle toutes les 0.2s
    const float enemyRate = 4.f;   // Un ennemi toutes les 2.5s
};