#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"

class GameObject {
public:
    virtual ~GameObject() = default;                // Virtual destructor for polymorphism

    virtual char getSymbol() const = 0;             // Abstract method to return the object's symbol
    virtual sf::Vector2f getPosition() const = 0;   // Abstract method to get the object's position
    virtual void setPosition(float newX, float newY) = 0; // Abstract method to set the object's position
    virtual void draw(sf::RenderWindow& window) const = 0; // Pure virtual draw method

protected:
    sf::Sprite m_sprite;  // Shared sprite for all game objects
    sf::Texture m_texture;
};
