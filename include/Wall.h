#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Robot;
class Wall;
class Rock;
class Door;
class Guard;

class Wall : public GameObject {
public:
    Wall();
    char getSymbol() const override;
    void draw(sf::RenderWindow& window) const override;
    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot& ) override {}
    void handleCollisionWith(Wall& ) override{}
    void handleCollisionWith(Rock& ) override {}
    void handleCollisionWith(Door& ) override {}
    void handleCollisionWith(Guard& ) override {}
    void handleCollisionWith(Present& ) override {}
    void handleCollisionWith(Bomb&, bool isExploding) override {}    
};
