#pragma once
#include "MovingGameObject.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <optional> // To handle the optional explosion time
static constexpr float EXPLOSION_DURATION = 2.0f; // Duration to show the explosion (in seconds)

class Bomb : public MovingGameObject {
public:
    Bomb();
    char getSymbol() const override;
    void update(const float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    void handleCollision(GameObject& other) override; 
    void handleCollisionWith(Robot& robot) override {} 
    void handleCollisionWith(Wall&) override {}        
    void handleCollisionWith(Rock&) override {}        
    void handleCollisionWith(Door&) override {}      
    void handleCollisionWith(Guard&) override {}       
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Bomb&, bool isExploding) override {}
    std::vector<sf::FloatRect> getExplosionPlusShapeBounds() const;
    sf::CircleShape getCollisionShape() const;
    const bool CheckBombExplode() const;
    const bool CanBeRemoved() const; 

private:
    void SetXplode();
    void markForRemoval();
    bool m_exploded;
    std::chrono::steady_clock::time_point m_startTime;
    std::optional<std::chrono::steady_clock::time_point> m_explosionTime; // Explosion start time

};
