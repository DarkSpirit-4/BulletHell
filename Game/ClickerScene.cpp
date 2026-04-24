#include "ClickerScene.h"
#include "Engine.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "WindowModule.h"
#include "ClickerLogic.h"
#include <iostream>

ClickerScene::ClickerScene()
    : Scene("ClickerScene", false)
{
}

void ClickerScene::Update(const float _delta_time)
{
    Scene::Update(_delta_time);

    if (!m_isInitialized) {
        InitScene();
    }
}

void ClickerScene::InitScene()
{
    auto* engine = Engine::GetInstance();
    auto* mm = engine->GetModuleManager();

    auto* assets = mm->GetModule<AssetsModule>();
    auto* windowMod = mm->GetModule<WindowModule>();

    if (!assets || !windowMod) return;

    std::cout << "[Clicker] Configuration de la fenêtre et des assets..." << std::endl;

    windowMod->SetSize(Maths::Vector2u(700, 700));
    windowMod->SetTitle("Sky Iron Clicker");

    GameObject* clickTarget = CreateGameObject("MainClicker");

    clickTarget->SetPosition(Maths::Vector2f(400.0f, 400.0f));

    Texture* tex = assets->GetAsset<Texture>("tileYellow_71.png");
    if (!tex) tex = assets->LoadAsset<Texture>("tileYellow_71.png");

    if (tex) clickTarget->CreateComponent<SpriteRenderer>(tex);

    clickTarget->CreateComponent<ClickerLogic>();

    m_isInitialized = true;
}