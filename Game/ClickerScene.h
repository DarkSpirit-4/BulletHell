#ifndef CLICKERSCENE_H
#define CLICKERSCENE_H

#include "Core/Scene.h"

class ClickerScene : public Scene
{
public:
    ClickerScene();

    void Update(const float _delta_time) override;
    void InitScene();

private:
    bool m_isInitialized = false;
};

#endif