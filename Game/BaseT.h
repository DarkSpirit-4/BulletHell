#ifndef BASET_H
#define BASET_H

#include "Core/Component.h"

class BaseT : public Component
{
public:
    void Awake() override;
    void TakeDamage(int _amount);

private:
    int m_hp = 10;
};

#endif