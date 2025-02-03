#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp> // Include only RenderWindow from SFML
#include <SFML/Window/Keyboard.hpp>       // Include for sf::Keyboard::Key

class MovingGameObject : public GameObject {
   // Velocity components (in units per second)

public:
    

    virtual sf::CircleShape getCollisionShape() const = 0;
    virtual void update(float deltaTime) = 0;          
   

};
