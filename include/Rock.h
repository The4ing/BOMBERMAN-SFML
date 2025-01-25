#pragma once
#include "GameObject.h"
#include <iostream>

class Rock : public GameObject {
public:
    Rock(const sf::Texture& texture); // Constructor to initialize the Rock with a texture

    char getSymbol() const override;  // Returns '#' to represent a Rock
    sf::Vector2f getPosition() const override; // Gets the Rock's position
    void setPosition(float x, float y) override; // Sets the Rock's position
    void draw(sf::RenderWindow& window) const override; // Draws the Rock on the screen
  
   

    void collideWith(GameObject* other) override;
    void collideWith(Guard* Guard) override;
    void collideWith(Robot* robot) override;
    


private:
    sf::Sprite m_sprite; // The Rock's visual representation
};
