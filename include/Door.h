#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Robot;
class Wall;
class Rock;
class Door;
class Guard;

class Door : public GameObject {
public:
    explicit Door(); 
    char getSymbol() const override; 
    void draw(sf::RenderWindow& window) const override; 
    void handleCollision(GameObject&) override; 
    void handleCollisionWith(Robot&) override {} 
    void handleCollisionWith(Wall&) override {}       
    void handleCollisionWith(Rock&) override {}        
    void handleCollisionWith(Door&) override {}      
    void handleCollisionWith(Guard&) override {}      
    void handleCollisionWith(Present& Present) override{}
    void handleCollisionWith(Bomb&, bool isExploding) override {}
};
