#pragma once

#include "MovingGameObject.h"
const int CIRCLRE_OFFSET = 10;
class Guard : public MovingGameObject {
protected:
    // Shared attributes and behavior for all guards
    sf::Sprite m_sprite;
    sf::Vector2f m_startingPosition;
    sf::Vector2f m_previousPosition;        // Guard's current velocity
    sf::Vector2f m_velocity;        // Guard's current velocity

    sf::CircleShape m_collisionShape;
    float m_frameWidth;
    float m_frameHeight;
    int m_animationFrame;           // frame of the animation

    void revertPosition();

public:
    Guard();


    static int getGuardCount();
    static void restartNumGuard();
    static void reduceNumGuard();
  

  



    void draw(sf::RenderWindow& window) const override;
    char getSymbol() const override;
    void setFreezeGaurd(const bool status);
    const bool getIsFreeze() const;
   

    
    virtual void setStartingPosition(float newX, float newY);
    virtual sf::Vector2f getStartingPosition();


    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot&) override {}
    void handleCollisionWith(Rock&) override;
    void handleCollisionWith(Door&) override;
    void handleCollisionWith(Present& ) override {}


private:
    bool m_freezeGuard;
    static int m_numGuard;
    
};



 
