//#pragma once
//#include "Core/Component.h"
//
//enum class GamePhase {
//    Asteroids1,
//    BulletHell,  // On garde le nom original
//    Asteroids2,
//    BulletHell2  // On ajoute juste celle-ci
//};
//
//class EnemyManager : public Component {
//public:
//    void Update(float _deltaTime) override;
//
//private:
//    void SpawnAsteroid();
//    void SpawnRainBullet();
//    void SpawnEnemy();
//
//    // Maintenant le compilateur comprend ce qu'est WavePhase
//    GamePhase currentPhase = GamePhase::AsteroidRain;
//    float phaseTimer = 0.0f;
//    float spawnTimer = 0.0f;
//    float enemyTimer = 0.0f;
//};