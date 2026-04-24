#include "MapRenderer.h"
#include "MapData.h"
#include "Engine.h"
#include "Modules/AssetsModule.h"
#include "Assets/Texture.h"
#include "Core/GameObject.h"

void MapRenderer::Awake()
{
    AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    if (assets) {
        m_grassTex = assets->LoadAsset<Texture>("towerDefense_tile222.png");
        m_pathTex = assets->LoadAsset<Texture>("towerDefense_tile241.png");
        m_baseTex = assets->LoadAsset<Texture>("spaceShips_001.png");
    }
}

void MapRenderer::Render(sf::RenderWindow* _window)
{
    if (!_window || !m_grassTex) return;

    for (int y = 0; y < MapData::HEIGHT; y++)
    {
        for (int x = 0; x < MapData::WIDTH; x++)
        {
            int tileID = MapData::level1[y][x];
            Texture* currentTex = nullptr;

            if (tileID == 0) currentTex = m_grassTex;
            else if (tileID == 1) currentTex = m_pathTex;
            else currentTex = m_baseTex;

            if (currentTex) {

                sf::Sprite tileSprite(currentTex->GetTexture());

                // Positionnement simple
                tileSprite.setPosition({ (float)x * MapData::TILE_SIZE, (float)y * MapData::TILE_SIZE });

                _window->draw(tileSprite);
            }
        }
    }
}