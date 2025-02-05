#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

class Robot;
class Wall;
class Rock;
class Door;
class Guard;
class Bomb;
class Present;
class Coin;

class GameObject {


 
public:
    virtual ~GameObject() = default;
    GameObject() = default;

    virtual void setTexture(const sf::Texture& texture);
    virtual sf::Sprite& getSprite();
    virtual const sf::Sprite& getSprite() const;


    virtual sf::Vector2f getPosition() const;
    virtual void setPosition(float newX, float newY) ;
    virtual sf::FloatRect getBoundingBox() const;
    virtual void setScale(float scaleX, float scaleY);
   

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual char getSymbol() const = 0;

    // Entry point for double dispatch
    virtual void handleCollision(GameObject& other) = 0;

    // Overloads for specific collision types
    virtual void handleCollisionWith(Robot&) = 0;
    virtual void handleCollisionWith(Wall&) = 0;
    virtual void handleCollisionWith(Rock&) = 0;
    virtual void handleCollisionWith(Door&) = 0;
    virtual void handleCollisionWith(Guard&) = 0;
    virtual void handleCollisionWith(Present&) = 0;
    virtual void handleCollisionWith(Bomb&, bool isExploding) = 0; // Add this!
    void handleCollisionWith(Coin&) {};

private:

    sf::Sprite m_sprite;
};
