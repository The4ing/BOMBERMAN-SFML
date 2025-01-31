#pragma once
#include "Guard.h"
#include <SFML/Graphics.hpp>
#include <random>

class SmartGuard : public Guard {
public:
    SmartGuard();

    char getSymbol() const override { return '!'; }
    void setPosition(float newX, float newY) override;
    sf::Vector2f getPosition() const override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    void handleCollision(GameObject& other) override;
    sf::FloatRect getBoundingBox() const override;

    // Specific collision handling
    void handleCollisionWith(Robot& robot) override;
    void handleCollisionWith(Wall& wall) override;
    void handleCollisionWith(Rock& rock) override;
    void handleCollisionWith(Door& door) override;
    void handleCollisionWith(Guard& guard) override;
    void handleCollisionWith(Present& Present) override;
    void handleCollisionWith(Bomb&, bool isExploding) override;        // No-op for Bomb

    void setScale(float scaleX, float scaleY) override;
    void setPlayerPosition(const sf::Vector2f& playerPos);
    
    void setStartingPosition(float newX, float newY) override;
    sf::Vector2f getStartingPosition() override;

    sf::CircleShape getCollisionShape() const override;
    // bool isBlocked(float newX, float newY);
    void setVelocity(Direction dir);
    void moveInAnyAvailableDirection();


private:

    void revertPosition();

    sf::Vector2f m_playerPosition; // Target player position
    sf::Vector2f m_velocity;
    sf::Clock m_directionChangeClock;
    sf::Time m_randomChangeInterval;
    sf::Clock m_animationClock;
    sf::Vector2f m_previousPosition;        // Guard's current velocity

    Direction preferredDirection;
    Direction alternateDirection;
    sf::CircleShape m_collisionShape;


    float m_speed;
    int m_animationFrame;
    float m_frameWidth;
    float m_frameHeight;
    bool m_collisionDetected;

   // sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_startingPosition;
    void calculateVelocity();  // Move toward player
    void randomizeBehavior();  // Randomize movement
    void updateAnimation();    // Update animation frame
};
