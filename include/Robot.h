#pragma once
#include "MovingGameObject.h"
#include <SFML/Graphics.hpp>
#include <set>
#include "Robot.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
#include "Guard.h"

// Constants
const float ROBOT_SPEED = 200.f;    // Speed in pixels per second
const int SPRITE_WIDTH = 20;        // Sprite width in pixels
const int SPRITE_HEIGHT = 30;       // Sprite height in pixels
const float ROBOT_SCALE = 2.0f;     // Scale factor

class Robot : public MovingGameObject {
public:
    Robot();
   

    // Overridden methods
    char getSymbol() const override { return '/'; }
    void update(float deltaTime) override;
    void handleInput(sf::Keyboard::Key key, bool isPressed);
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

    //virtual sf::FloatRect getBoundingBox() const override;
    // Grid-related helper
    sf::Vector2i getCurrentCell() const; // Return the grid cell dynamically

    sf::CircleShape getCollisionShape() const override;

private:
    bool validKeys(sf::Keyboard::Key key);
    Direction m_direction;           // Current movement direction
    bool m_arrowKeyPressed;          // Flag for movement animation
    std::set<sf::Keyboard::Key> activeKeys; // Store currently pressed keys
    sf::Vector2f m_velocity;
    sf::Vector2f m_previousPosition;
    int lastDirection;

   
    // Animation-related members
    int m_animationFrame;            // Current animation frame index
    sf::Clock m_animationClock;      // Clock for animation timing
    sf::Time m_animationTimer;       // Time per animation frame
    sf::CircleShape m_collisionShape;
    bool m_robotHit;
};
