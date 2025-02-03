#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Robot;
class Wall;
class Rock;
class Door;
class Guard;

class Rock : public GameObject {
public:
    explicit Rock(); // Constructor to initialize the Rock with a texture
    char getSymbol() const override;  // Returns '#' to represent a Rock
    void draw(sf::RenderWindow& window) const override; // Draws the Rock on the screen



    void handleCollision(GameObject& other) override; // Double dispatch entry point
    void handleCollisionWith(Robot& ) override {}// Handle collision with a Robot
    void handleCollisionWith(Wall&) override {}        // No-op for Wall
    void handleCollisionWith(Rock&) override {}      // No-op for another Rock
    void handleCollisionWith(Door&) override {}        // No-op for Door
    void handleCollisionWith(Guard&) override {}       // No-op for Guard
    void handleCollisionWith(Present& ) override {}
    void handleCollisionWith(Bomb&, bool ) override {}       // No-op for Bomb
    


};
