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
    //sf::Vector2f getPosition() const override;
    char getSymbol() const override;
    void draw(sf::RenderWindow& window) const override;

   // void setPosition(float x, float y) override;
    /*sf::FloatRect getBoundingBox() const override;
    void setScale(float scaleX, float scaleY) override;*/


    void handleCollision(GameObject& other) override;

    // Handle collisions with specific types
    void handleCollisionWith(Robot& ) override {}
    void handleCollisionWith(Wall& ) override{}
    void handleCollisionWith(Rock& ) override {}
    void handleCollisionWith(Door& ) override {}
    void handleCollisionWith(Guard& ) override {}
    void handleCollisionWith(Present& ) override {}
    void handleCollisionWith(Bomb& , bool) override {}    // No-op for Bomb

   

private:
    //sf::Sprite m_sprite;
};
