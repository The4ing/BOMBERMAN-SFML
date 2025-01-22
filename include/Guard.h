#pragma once

#include "MovingGameObject.h"

class Guard : public MovingGameObject {
protected:
    // Shared attributes and behavior for all guards
    int guardID;
    float detectionRange;

public:
    Guard() : guardID(0), detectionRange(100.0f) {}
    virtual void colision() = 0; // Pure virtual function

};



 