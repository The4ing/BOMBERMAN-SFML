#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Robot;
class Wall;
class Rock;
class Door;
class Guard;

class Wall : public GameObject {
public:
    Wall(const sf::Texture& texture);

    char getSymbol() const override;
    sf::Vector2f getPosition() const override;
    void setPosition(float x, float y) override;
    void draw(sf::RenderWindow& window) const override;
    sf::FloatRect getBoundingBox() const override;

    void handleCollision(GameObject& other) override;

    // Handle collisions with specific types
    void handleCollisionWith(Robot& robot) override;
    void handleCollisionWith(Wall& wall) override;
    void handleCollisionWith(Rock& rock) override;
    void handleCollisionWith(Door& door) override;
    void handleCollisionWith(Guard& guard) override;
    void handleCollisionWith(Bomb& Bomb, bool isExploding) override;       // No-op for Bomb

    void setScale(float scaleX, float scaleY);

private:
    sf::Sprite m_sprite;
};
