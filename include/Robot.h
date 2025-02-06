#pragma once
#include "MovingGameObject.h"
#include <SFML/Graphics.hpp>
#include <set>
#include "Robot.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
#include "Guard.h"

class Robot : public MovingGameObject {
public:
    Robot();
    char getSymbol() const override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot& ) override{}
    void handleCollisionWith(Wall& wall) override;
    void handleCollisionWith(Rock& rock) override;
    void handleCollisionWith(Door& door) override;
    void handleCollisionWith(Guard& guard) override;
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Bomb&, bool isExploding) override;        // No-op for Bomb
    void resolveCollision(const GameObject& object);
    const bool isRobotHit() const ;
    void setHitStatus(bool status);
    sf::CircleShape getCollisionShape() const override;

private:
    Direction m_direction; 
    sf::Vector2f m_velocity;
    sf::Vector2f m_previousPosition;
    int m_animationFrame;            
    sf::Clock m_animationClock;      
    sf::Time m_animationTimer;      
    bool m_robotHit;
};
