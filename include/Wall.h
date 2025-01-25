#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Wall : public GameObject {
public:
    Wall(const sf::Texture& texture); // Constructor to initialize the wall with a texture

    char getSymbol() const override;  // Returns '#' to represent a wall
    sf::Vector2f getPosition() const override; // Gets the wall's position
    void setPosition(float x, float y) override; // Sets the wall's position
    void draw(sf::RenderWindow& window) const override; // Draws the wall on the screen
  




    void collideWith(GameObject* other) override;
    void collideWith(Robot* robot) override;
    void collideWith(Guard* Guard) override;


  



private:
    sf::Sprite m_sprite; // The wall's visual representation
};
