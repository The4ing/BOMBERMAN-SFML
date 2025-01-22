// wall.h
#pragma once
#include "GameObject.h"

class Wall : public GameObject {
public:
    char getSymbol() const override { return '#'; }
    sf::Vector2f getPosition() const override;
    void setPosition(float x, float y) override;
};

