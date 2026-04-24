#include "BaseT.h"
#include <iostream>

void BaseT::Awake()
{
    m_hp = 10;
    std::cout << "[Base] Base installee. PV : " << m_hp << std::endl;
}

void BaseT::TakeDamage(int _amount)
{
    m_hp -= _amount;

    if (m_hp > 0)
    {
        std::cout << "[Base] ATTENTION ! La base a ete touchee ! PV restants : " << m_hp << std::endl;
    }
    else
    {
        m_hp = 0;
        std::cout << "[Base] GAME OVER ! La base a ete detruite !" << std::endl;

    }
}