#pragma once
#include "MovingGameObject.h"
#include <SFML/Graphics.hpp>
#include "Utilities.h"

// Sprite-related constants
const float ROBOT_SPEED = 200.f;    // Speed of the robot in pixels per second
const int SPRITE_WIDTH = 20;        // Width of each sprite frame in the spritesheet
const int SPRITE_HEIGHT = 30;       // Height of each sprite frame in the spritesheet
const int ANIMATION_FRAMES = 3;     // Number of frames per animation cycle (3 per direction)
const float ROBOT_SCALE = 3.0f;     // Scale factor (3.0 means triple the size)

class Robot : public MovingGameObject {
public:
    // Constructor
    Robot();

    // Overridden method to return the symbol of the Robot
    char getSymbol() const override { return '/'; }

    // Updates the robot's position and animation
    void update(float deltaTime) override;

    // Handles keyboard input for movement
    void handleInput(sf::Keyboard::Key key, bool isPressed);

    // Draws the robot on the window
    void draw(sf::RenderWindow& window) const;

    // Setters and getters for velocity and position
    void setVelocity(float vx, float vy);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);

private:
    sf::Sprite m_sprite;             // Robot's sprite
    sf::Texture m_texture;           // Texture for the robot's spritesheet

    sf::Vector2f m_velocity;         // Current velocity of the robot
    Direction m_direction;           // Current movement direction
    bool m_arrowKeyPressed;          // Flag for active movement

    // Animation-related members
    int m_animationFrame;            // Current animation frame index
    sf::Clock m_animationClock;      // Clock for animation timing
    sf::Time m_animationTimer;       // Time per animation frame
};
