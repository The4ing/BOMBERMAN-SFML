#pragma once

#include "MovingGameObject.h"
const int CIRCLRE_OFFSET = 10;
class Guard : public MovingGameObject {
protected:
    // Shared attributes and behavior for all guards
    int guardID;
    float detectionRange;

public:
    Guard() : guardID(0), detectionRange(100.0f) {}
  //  virtual void colision() = 0; // Pure virtual function
    virtual void setScale(float scaleX, float scaleY) = 0;
  //  virtual void reverseDirection() = 0; 
    //    m_direction.x = -m_direction.x; // Reverse X direction
    //    m_direction.y = -m_direction.y; // Reverse Y direction
    //}

};



 
