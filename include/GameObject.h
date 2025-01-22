#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"


class GameObject {
public:
    virtual char getSymbol() const = 0; // Abstract method for getting symbol representation
    virtual ~GameObject() = default;    // Virtual destructor
    virtual sf::Vector2f getPosition() const = 0;
    virtual  void setPosition(float newX, float newY) = 0;

protected:


    sf::Sprite m_sprite;             // Robot's sprite
    sf::Texture m_texture;
    //sf::Vector2f m_velocity = { 0.0f, 0.0f }; // Correct initialization with braces
    //sf::Vector2f m_currentCell = { 0.0f, 0.0f };

   
};

