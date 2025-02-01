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
    virtual void setStartingPosition(float newX, float newY);
    virtual sf::Vector2f getStartingPosition();
    char getSymbol() const override;
    void setPosition(float newX, float newY) override;
    sf::Vector2f getPosition() const override;
    sf::FloatRect getBoundingBox() const override;
    void draw(sf::RenderWindow& window) const override;
    virtual void setScale(float scaleX, float scaleY);


    void handleCollision(GameObject& other) override;
    void handleCollisionWith(Robot&) override {}
    void handleCollisionWith(Rock&) override;
    void handleCollisionWith(Door&) override;
    void handleCollisionWith(Present& ) override {}


  

    
  //  virtual void colision() = 0; // Pure virtual function
  
  //  virtual void reverseDirection() = 0; 
    //    m_direction.x = -m_direction.x; // Reverse X direction
    //    m_direction.y = -m_direction.y; // Reverse Y direction
    //}

    

};



 
