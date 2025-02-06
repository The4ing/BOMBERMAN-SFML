#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp> 
#include <SFML/Window/Keyboard.hpp>       

class MovingGameObject : public GameObject {
 
public:
    virtual sf::CircleShape getCollisionShape() const = 0;
    virtual void update(float) = 0;          
};
