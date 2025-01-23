#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Door : public GameObject {
public:
    Door(const sf::Texture& texture); // Constructor to initialize the wall with a texture

    char getSymbol() const override;  // Returns 'D' to represent a wall
    sf::Vector2f getPosition() const override; // Gets the wall's position
    void setPosition(float x, float y) override; // Sets the wall's position
    void draw(sf::RenderWindow& window) const override; // Draws the wall on the screen

private:
    sf::Sprite m_sprite; // The wall's visual representation
};
