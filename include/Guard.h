#pragma once
#include <iostream>
#include "MovingGameObject.h"

class Guard : public MovingGameObject {
protected:

   
    // Shared attributes and behavior for all guards
    int guardID;
    float detectionRange;
  

public:
    Guard() : guardID(0), detectionRange(100.0f) {}
   
    void collideWith(GameObject* other) override;
    void collideWith(Rock* rock) override;
    void collideWith(Wall* wall) override;
    void collideWith(Door* door) override;
    void collideWith(Guard* Guard) override;
    void collideWith(Robot* robot) override;

};



 