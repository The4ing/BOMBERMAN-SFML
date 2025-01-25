#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp> // Include only RenderWindow from SFML
#include <SFML/Window/Keyboard.hpp>       // Include for sf::Keyboard::Key

class MovingGameObject : public GameObject {
   // Velocity components (in units per second)

public:
    
   // virtual void setVelocity(float newVX, float newVY) = 0;
   

    virtual void collideWith(GameObject* other) = 0;  // Abstract method for collision handling
    virtual void collideWith(Wall* wall) = 0;  // Abstract method for collision handling
    virtual void collideWith(Door* door) = 0;  // Abstract method for collision handling
    virtual void collideWith(Rock* rock) = 0;
    virtual void update(float deltaTime) = 0;                 // Pure virtual update
   // virtual void draw(sf::RenderWindow& window) const = 0;    // Pure virtual draw
   // virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0; // Handle input
    

};
