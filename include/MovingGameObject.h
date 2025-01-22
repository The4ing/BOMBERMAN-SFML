#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp> // Include only RenderWindow from SFML
#include <SFML/Window/Keyboard.hpp>       // Include for sf::Keyboard::Key

class MovingGameObject : public GameObject {
protected:
    float x, y;       // Floating-point position for smooth movement
    float vx, vy;     // Velocity components (in units per second)

public:
    MovingGameObject() : x(0), y(0), vx(0), vy(0) {}

   

    virtual void setVelocity(float newVX, float newVY) = 0;
   


    virtual void update(float deltaTime) = 0;                 // Pure virtual update
    virtual void draw(sf::RenderWindow& window) const = 0;    // Pure virtual draw
    virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0; // Handle input
    

    float getX() const { return x; }
    float getY() const { return y; }
};
