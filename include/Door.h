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


    explicit Door(); // Constructor to initialize the door with a texture
    char getSymbol() const override;  // Returns 'D' to represent a door
    void draw(sf::RenderWindow& window) const override; // Draws the door on the screen

    void handleCollision(GameObject&) override; // Double dispatch entry point
    void handleCollisionWith(Robot&) override {} // Handle collision with a Robot
    void handleCollisionWith(Wall&) override {}       // No-op for Wall
    void handleCollisionWith(Rock&) override {}        // No-op for Rock
    void handleCollisionWith(Door&) override {}       // No-op for another Door
    void handleCollisionWith(Guard&) override {}      // No-op for Guard
    void handleCollisionWith(Present& Present) override{}
    void handleCollisionWith(Bomb&, bool) override {}       // No-op for Bomb
   


};
