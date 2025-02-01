#pragma once

#include "Guard.h"
#include <SFML/Graphics.hpp>
#include <random>

class StupidGuard : public Guard {
public:
    StupidGuard();

    // Overridden methods
    
   
    
    void update(float deltaTime) override;
    
   

    // Specific collision handling
    
    void handleCollisionWith(Wall&) override;
    void handleCollisionWith(Guard& ) override;
    void handleCollisionWith(Bomb&, bool ) override;        // No-op for Bomb

    
    sf::CircleShape getCollisionShape() const override;

    
private:
    // Helper Methods
    void changeDirection();
   
    // Animation-related members
   // sf::Texture m_texture;          // Texture for the guard's sprite

    // Sprite for the guard
  

    sf::Clock m_animationClock;     // Clock for animating the guard
    sf::Clock m_movementClock;      // Clock for changing direction
    sf::Time m_randomChangeInterval; // Interval to change direction
    sf::Time m_timeSinceLastChange;
    sf::Time m_animationTimeSinceLastChange;
    sf::Vector2f m_startingPosition;
    
    // Movement-related members
   
    
    Direction m_direction;          // Current movement direction
};
