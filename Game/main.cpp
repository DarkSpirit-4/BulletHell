#include "Engine.h"
#include "Modules/SceneModule.h"

#include "MenuScene.h"
#include "Scenes/DefaultScene.h"
#include "TowerDefenseScene.h"

int main(const int _argc, const char** _argv)
{
    Engine* const engine = Engine::GetInstance();
    engine->Init(_argc, _argv);

    auto* sm = engine->GetModuleManager()->GetModule<SceneModule>();

    sm->CreateScene<MenuScene>();
    sm->CreateScene<BulletHellScene>();
    sm->CreateScene<TowerDefenseScene>();

    engine->Run();
    return 0;
}