// wall.h
#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
    char getSymbol() const override { return '#'; }
};
