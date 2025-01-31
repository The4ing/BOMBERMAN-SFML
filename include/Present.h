#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Present : public GameObject {
public:
    Present();  // Pass texture as const reference



    virtual ~Present() = default;

    // Manage the count of presents
    static int getPresentCount();
    static void addNumPresent();
    static void restartNumPresent();
    static void reduceNumPresent();

    // GameObject overrides
    virtual char getSymbol() const override = 0;
    virtual sf::Vector2f getPosition() const override;
    virtual void setPosition(float newX, float newY) override;
    virtual void draw(sf::RenderWindow& window) const override;
    virtual sf::FloatRect getBoundingBox() const override;
    virtual void setActive();
    virtual const bool checkActive();
    void setScale(float scaleX, float scaleY);



    virtual void handleCollision(GameObject& other) override;
    virtual void handleCollisionWith(Robot& robot) override;
    void handleCollisionWith(Present&) override {}
    void handleCollisionWith(Wall&) override {}
    void handleCollisionWith(Rock&) override {}
    void handleCollisionWith(Door&) override {}
    void handleCollisionWith(Guard&) override {}
    void handleCollisionWith(Bomb&, bool) override {}

protected:
    sf::Vector2f m_position;
    sf::Sprite m_sprite;
    bool m_activePresent;

private:
    static int m_numPresent;

};
