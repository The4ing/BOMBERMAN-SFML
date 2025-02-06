#pragma once

#include "Guard.h"
#include <SFML/Graphics.hpp>
#include <random>

class StupidGuard : public Guard {
public:
    StupidGuard();
    void update(float deltaTime) override;
    void handleCollisionWith(Guard&) override {}
    void handleCollisionWith(Bomb&, bool isExploding) override;  
    sf::CircleShape getCollisionShape() const override;

private:
    void changeDirection();
    sf::Time m_randomChangeInterval; 
    sf::Time m_timeSinceLastChange;
    sf::Time m_animationTimeSinceLastChange;
    Direction m_direction;        
};
