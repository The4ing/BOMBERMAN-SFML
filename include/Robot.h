#pragma once
#include "MovingGameObject.h"
#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include <set>

// Constants
const float ROBOT_SPEED = 200.f;    // Speed in pixels per second
const int SPRITE_WIDTH = 20;        // Sprite width in pixels
const int SPRITE_HEIGHT = 30;       // Sprite height in pixels
const float ROBOT_SCALE = 3.0f;     // Scale factor

class Robot : public MovingGameObject {
public:
    Robot();
  

    // Overridden methods
    char getSymbol() const override { return '/'; }
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void draw(sf::RenderWindow& window) const override;
    void setPosition(float x, float y) override;
    sf::Vector2f getPosition() const override;

    // Grid-related helper
    sf::Vector2i getCurrentCell() const; // Return the grid cell dynamically

private:
    Direction m_direction;           // Current movement direction
    bool m_arrowKeyPressed;          // Flag for movement animation
    std::set<sf::Keyboard::Key> activeKeys; // Store currently pressed keys

    sf::Vector2f m_velocity;
    int lastDirection;

    // Animation-related members
    int m_animationFrame;            // Current animation frame index
    sf::Clock m_animationClock;      // Clock for animation timing
    sf::Time m_animationTimer;       // Time per animation frame
};
