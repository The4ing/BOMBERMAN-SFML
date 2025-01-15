#pragma once
#include "GameObject.h"

class Door : public GameObject {
public:
    char getSymbol() const override { return 'D'; }
};

