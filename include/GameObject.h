#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include <iostream>

class Robot;  // Forward declaration
class Wall;
class Guard;  // Forward declaration
class Door;
class Rock;
class Bomb;

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void collideWith(GameObject* other) = 0;
    virtual void collideWith(Robot* robot) = 0;
    virtual void collideWith(Guard* guard) = 0;
    virtual void collideWith(Bomb* bomb) = 0;



    virtual sf::FloatRect getGlobalBounds() const {
        return m_sprite.getGlobalBounds();
    }

    virtual char getSymbol() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(float newX, float newY) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

protected:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
};
