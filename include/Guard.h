#pragma once
#include "MovingGameObject.h"

class Guard : public MovingGameObject {
public:
    Guard();
   // static int getGuardCount();
    //static void restartNumGuard();
    //static void reduceNumGuard();
    void draw(sf::RenderWindow& window) const override;
    char getSymbol() const override;
    void setFreezeGaurd(const bool status);
    const bool getIsFreeze() const;
    void setVelocity(const sf::Vector2f velocity);
    sf::Vector2f getVelocity();
    void getRevert();
    void setAnimation(const int UpdateAnim);
    const int getAnimation();
    void setPrevPpos(const sf::Vector2f velocity);
    const float getFrameWidth() const;
    const float getFrameHight() const ;
    virtual void setStartingPosition(float newX, float newY);
    virtual sf::Vector2f getStartingPosition();
    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot&) override {}
    void handleCollisionWith(Rock&) override;
    void handleCollisionWith(Wall&) override;
    void handleCollisionWith(Door&) override;
    void handleCollisionWith(Present& ) override {}

private:
    void revertPosition();
    sf::Vector2f m_previousPosition;        // Guard's current velocity
    sf::Vector2f m_startingPosition;
    sf::Vector2f m_velocity;
    bool m_freezeGuard;
    int m_animationFrame;           // frame of the animation
    float m_frameWidth;
    float m_frameHeight;
};
