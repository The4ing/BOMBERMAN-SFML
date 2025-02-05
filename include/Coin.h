#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Coin : public GameObject {
public:
    explicit Coin();  // Constructor
    char getSymbol() const override;
    void draw(sf::RenderWindow& window) const override;
    void update(float deltaTime);  // Function to update animation
    sf::CircleShape getCollisionShape() const;

    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot&) override {}// Handle collision with a Robot
    void handleCollisionWith(Wall&) override {}        // No-op for Wall
    void handleCollisionWith(Rock&) override {}      // No-op for another Rock
    void handleCollisionWith(Door&) override {}        // No-op for Door
    void handleCollisionWith(Guard&) override {}       // No-op for Guard
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Bomb&, bool) override {}       // No-op for Bomb

private:
    sf::IntRect frameRect;   // Defines the current frame
    float frameTime;         // Time per frame
    float elapsedTime;       // Time elapsed since last frame update
    int frameIndex;          // Current frame index
    int totalFrames;         // Total frames in sprite sheet
};
