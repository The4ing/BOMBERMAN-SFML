#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
class Robot;
class Wall;
class Rock;
class Door;
class Guard;
class Bomb;

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual char getSymbol() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(float newX, float newY) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual sf::FloatRect getBoundingBox() const = 0;

    // Entry point for double dispatch
    virtual void handleCollision(GameObject& other) = 0;

    // Overloads for specific collision types
    virtual void handleCollisionWith(Robot&) = 0;
    virtual void handleCollisionWith(Wall&) = 0;
    virtual void handleCollisionWith(Rock&) = 0;
    virtual void handleCollisionWith(Door&) = 0;
    virtual void handleCollisionWith(Guard&) = 0;
    virtual void handleCollisionWith(Bomb&, bool isExploding) = 0; 
};
