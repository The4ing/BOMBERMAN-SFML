#pragma once
#include "GameObject.h"

class MovingGameObject : public GameObject {
protected:
    float x, y;       // Floating-point position for smooth movement
    float vx, vy;     // Velocity components (in units per second)

public:
    MovingGameObject() : x(0), y(0), vx(0), vy(0) {}

    void setPosition(float newX, float newY) {
        x = newX;
        y = newY;
    }

    void setVelocity(float newVX, float newVY) {
        vx = newVX;
        vy = newVY;
    }

    virtual void update(float deltaTime) = 0; // Pure virtual update

    float getX() const { return x; }
    float getY() const { return y; }
};
