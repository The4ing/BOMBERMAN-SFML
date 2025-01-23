#pragma once

#include "Guard.h"
#include <SFML/Graphics.hpp>
#include <random>

class StupidGuard : public Guard {
public:
    StupidGuard();

    // Overridden methods
    char getSymbol() const override { return '!'; }
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() const override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

private:
    // Helper Methods
    void changeDirection();

    // Animation-related members
    sf::Texture m_texture;          // Texture for the guard's sprite
    sf::Sprite m_sprite;            // Sprite for the guard
    int m_frameWidth;               // Width of a single frame
    int m_frameHeight;              // Height of a single frame
    int m_animationFrame;           // frame of the animation
    sf::Clock m_animationClock;     // Clock for animating the guard
    sf::Clock m_movementClock;      // Clock for changing direction
    sf::Time m_randomChangeInterval; // Interval to change direction
    sf::Time m_timeSinceLastChange;
    sf::Time m_animationTimeSinceLastChange;

    // Movement-related members
    sf::Vector2f m_velocity;        // Guard's current velocity
    Direction m_direction;          // Current movement direction
};
