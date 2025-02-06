#pragma once
#include "Guard.h"
#include <SFML/Graphics.hpp>
#include <random>

class SmartGuard : public Guard {
public:
    SmartGuard();
    void update(float deltaTime) override;
    void handleCollisionWith(Guard&) override;
    void handleCollisionWith(Bomb&, bool isExploding) override; 
    void setPlayerPosition(const sf::Vector2f& playerPos);
    sf::CircleShape getCollisionShape() const override;
    void updateVelocity(Direction dir);

private:
    void calculateVelocity();
    void randomizeBehavior();
    void updateAnimation();
    sf::Vector2f m_playerPosition; 
    sf::Clock m_directionChangeClock;
    sf::Time m_randomChangeInterval;
    sf::Clock m_animationClock;
    sf::Clock m_directionLockClock; 
    Direction preferredDirection;
    Direction alternateDirection;
    float m_speed;
};
