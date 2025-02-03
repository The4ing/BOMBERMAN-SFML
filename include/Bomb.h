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
 

    void handleCollision(GameObject& other) override; // Double dispatch entry point
    void handleCollisionWith(Robot& robot) override {} // Handle collision with a Robot
    void handleCollisionWith(Wall&) override {}        // No-op for Wall
    void handleCollisionWith(Rock&) override {}        // No-op for another Rock
    void handleCollisionWith(Door&) override {}       // No-op for Door
    void handleCollisionWith(Guard&) override {}       // No-op for Guard
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Bomb&, bool ) override {}       // No-op for Bomb

    std::vector<sf::FloatRect> getExplosionPlusShapeBounds() const;

    sf::CircleShape getCollisionShape() const;
    sf::FloatRect getExplosionArea() const;
    const bool CheckBombExplode() const;
    const bool CanBeRemoved() const; // Check if the bomb should be removed from the game
    void markForRemoval();

private:
  
    void SetXplode();
    bool m_exploded;
    std::chrono::steady_clock::time_point m_startTime;
    std::optional<std::chrono::steady_clock::time_point> m_explosionTime; // Explosion start time

};
