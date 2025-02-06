#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Coin : public GameObject {
public:
    explicit Coin();  
    char getSymbol() const override;
    void draw(sf::RenderWindow& window) const override;
    void update(float deltaTime); 
    sf::CircleShape getCollisionShape() const;
    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot&) override {}
    void handleCollisionWith(Wall&) override {}       
    void handleCollisionWith(Rock&) override {}    
    void handleCollisionWith(Door&) override {}        
    void handleCollisionWith(Guard&) override {}       
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Bomb&, bool isExploding) override {}      

private:
    sf::IntRect frameRect;   
    float frameTime;       
    float elapsedTime;       
    int frameIndex;          
    int totalFrames;         
};
