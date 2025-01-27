#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Robot;
class Wall;
class Rock;
class Door;
class Guard;

class Door : public GameObject {
public:
    explicit Door(const sf::Texture& texture); // Constructor to initialize the door with a texture

    char getSymbol() const override;  // Returns 'D' to represent a door
    sf::Vector2f getPosition() const override; // Gets the door's position
    void setPosition(float x, float y) override; // Sets the door's position
    void draw(sf::RenderWindow& window) const override; // Draws the door on the screen
    sf::FloatRect getBoundingBox() const override; // Returns the bounding box

    void handleCollision(GameObject& other) override; // Double dispatch entry point
    void handleCollisionWith(Robot& robot) override; // Handle collision with a Robot
    void handleCollisionWith(Wall&) override;        // No-op for Wall
    void handleCollisionWith(Rock&) override;        // No-op for Rock
    void handleCollisionWith(Door&) override;        // No-op for another Door
    void handleCollisionWith(Guard&) override;       // No-op for Guard
    void handleCollisionWith(Bomb&, bool isExploding) override;        // No-op for Bomb
    void setScale(float scaleX, float scaleY);

private:
    sf::Sprite m_sprite; // The door's visual representation
};
