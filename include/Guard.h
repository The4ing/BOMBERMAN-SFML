#pragma once
#include "MovingGameObject.h"

class Guard : public MovingGameObject {
public:
    Guard() {
        // Example: Default patrol velocity
        setVelocity(0.0f, 50.0f); // Moves 50 units/sec vertically
    }
    //char getSymbol() const override;
    void update(float deltaTime) override {
        // Update position based on velocity
        x += vx * deltaTime;
        y += vy * deltaTime;

        // Add custom AI movement logic here (e.g., patrolling behavior)
    }
};
