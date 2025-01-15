#pragma once
#include "MovingGameObject.h"

class Robot : public MovingGameObject {
public:
    Robot() {
        // Example: Default velocity
        setVelocity(100.0f, 0.0f); // Moves 100 units/sec horizontally
    }
    char getSymbol() const override { return '/'; }

    void update(float deltaTime) override {
        // Update position based on velocity
        x += vx * deltaTime;
        y += vy * deltaTime;

        // Example: Clamp position to stay within bounds (optional)
        if (x < 0) x = 0;
        if (y < 0) y = 0;

        // Add custom logic for player input (e.g., WASD/Arrow keys)
    }
};

