#pragma once
#include "GameObject.h"

class Rock : public GameObject {
public:
    char getSymbol() const override { return '@'; }
};

