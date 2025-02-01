#pragma once
#include "Guard.h"
#include <SFML/Graphics.hpp>
#include <random>

class SmartGuard : public Guard {
public:
    SmartGuard();

   
    void update(float deltaTime) override;
    

    // Specific collision handling
    
    void handleCollisionWith(Wall&) override;
    void handleCollisionWith(Guard&) override;
    void handleCollisionWith(Bomb&, bool) override;        // No-op for Bomb

    
    void setPlayerPosition(const sf::Vector2f& playerPos);


    sf::CircleShape getCollisionShape() const override;
   

    
    // bool isBlocked(float newX, float newY);
    void setVelocity(Direction dir);
    void moveInAnyAvailableDirection();


private:

    sf::Vector2f m_playerPosition; // Target player position
    sf::Clock m_directionChangeClock;
    sf::Time m_randomChangeInterval;
    sf::Clock m_animationClock;
   

    Direction preferredDirection;
    Direction alternateDirection;
    
    float m_speed;
    
    
    bool m_collisionDetected;

   // sf::Texture m_texture;
    sf::Vector2f m_startingPosition;

  
    void calculateVelocity();  // Move toward player
    void randomizeBehavior();  // Randomize movement
    void updateAnimation();    // Update animation frame
};
