#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Present : public GameObject {
public:
    Present();  
    virtual ~Present() = default;
    static int getPresentCount();
    static void reduceNumPresent();
    virtual char getSymbol() const override = 0;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual void handleCollision(GameObject& other) override;
    virtual void handleCollisionWith(Robot& robot) override;
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Wall&) override {}
    void handleCollisionWith(Rock&) override {}
    void handleCollisionWith(Door&) override {}
    void handleCollisionWith(Guard&) override {}
    void handleCollisionWith(Bomb&, bool isExploding) override {}

private:
    static int m_numPresent;

};
