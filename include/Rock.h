#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Robot;
class Wall;
class Rock;
class Door;
class Guard;

class Rock : public GameObject {
public:
    explicit Rock(const sf::Texture& texture); // Constructor to initialize the Rock with a texture

    char getSymbol() const override;  // Returns '#' to represent a Rock
    sf::Vector2f getPosition() const override; // Gets the Rock's position
    void setPosition(float x, float y) override; // Sets the Rock's position
    void draw(sf::RenderWindow& window) const override; // Draws the Rock on the screen
    sf::FloatRect getBoundingBox() const override; // Returns the bounding box

    void handleCollision(GameObject& other) override; // Double dispatch entry point
    void handleCollisionWith(Robot& robot) override; // Handle collision with a Robot
    void handleCollisionWith(Wall&) override;        // No-op for Wall
    void handleCollisionWith(Rock&) override;        // No-op for another Rock
    void handleCollisionWith(Door&) override;        // No-op for Door
    void handleCollisionWith(Guard&) override;       // No-op for Guard
    void handleCollisionWith(Bomb&, bool isExploding) override;       // No-op for Bomb
    void setScale(float scaleX, float scaleY);

private:
    sf::Sprite m_sprite; // The Rock's visual representation
};
