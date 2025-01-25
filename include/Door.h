#pragma once
#include "GameObject.h"
#include <iostream>


class Door : public GameObject {
public:
    Door(const sf::Texture& texture); // Constructor to initialize the wall with a texture

    char getSymbol() const override;  // Returns 'D' to represent a wall
    sf::Vector2f getPosition() const override; // Gets the wall's position
    void setPosition(float x, float y) override; // Sets the wall's position
    void draw(sf::RenderWindow& window) const override; // Draws the wall on the screen
   

    void collideWith(GameObject* other) override;
    void collideWith(Guard* Guard) override;
    void collideWith(Robot* robot) override;
    


private:
    sf::Sprite m_sprite; // The wall's visual representation
};
