#include "SmartGuard.h"
#include <cmath>
#include <iostream>

SmartGuard::SmartGuard()
    : m_speed(50.f),
    m_randomChangeInterval(sf::seconds(3.f))
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sprite& sprite = getSprite();
    sprite.setTexture(resourceManager.getTexture("smartGuardSprite.png"));
    sprite.setTextureRect(sf::IntRect(0, 0,static_cast<int>(getFrameWidth()), static_cast<int>(getFrameHight())));
    randomizeBehavior();
}

void SmartGuard::setPlayerPosition(const sf::Vector2f& playerPos) {
    m_playerPosition = playerPos;
}

void SmartGuard::randomizeBehavior() {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> intervalDist(2.f, 5.f);

    // Randomize next direction change interval
    m_randomChangeInterval = sf::seconds(intervalDist(generator));

    // Optional: Add slight random offset to velocity for unpredictable movement
    static std::uniform_real_distribution<float> offsetDist(-50.f, 50.f);
    sf::Vector2f velocity = { getVelocity().x + offsetDist(generator),getVelocity().y + offsetDist(generator) };
    setVelocity(velocity);
   
}

void SmartGuard::calculateVelocity() {
    sf::Vector2f direction = m_playerPosition - getPosition();
    float distanceX = std::abs(direction.x);
    float distanceY = std::abs(direction.y);

    if (distanceX > distanceY) {
        preferredDirection = (direction.x > 0) ? RIGHT : LEFT;
        alternateDirection = (direction.y > 0) ? DOWN : UP;
    }
    else {
        preferredDirection = (direction.y > 0) ? DOWN : UP;
        alternateDirection = (direction.x > 0) ? RIGHT : LEFT;
    }

    updateVelocity(preferredDirection);
}

void SmartGuard::updateAnimation() {

    sf::Sprite& sprite = getSprite();
    if (m_animationClock.getElapsedTime() >= sf::milliseconds(100)) {
        setAnimation((getAnimation() + 1) % 4);
        m_animationClock.restart();
    }

    int textureX = getAnimation() * static_cast<int>(getFrameWidth());
    int textureY = 0;

    if (getVelocity().y > 0) {
        textureY = 0;  // Moving down
    }
    else if (getVelocity().y < 0) {
        textureY = static_cast<int>(getFrameHight() * 2);  // Moving up
    }
    else if (getVelocity().x > 0) {
        textureY = static_cast<int>(getFrameHight());  // Moving right
    }
    else if (getVelocity().x < 0) {
        textureY = static_cast<int>(getFrameHight());  // Moving left
    }

    sprite.setTextureRect(sf::IntRect(textureX, textureY, static_cast<int>(getFrameWidth()), static_cast<int>(getFrameHight())));
}

void SmartGuard::update(float deltaTime) {
    sf::Sprite& sprite = getSprite();
    setPrevPpos(getPosition());

    // Change direction only if 2 seconds have passed
    if (m_directionLockClock.getElapsedTime().asSeconds() >= 2.0f) {
        calculateVelocity();
        m_directionLockClock.restart();
    }

    sprite.move(getVelocity() * deltaTime);
    updateAnimation();
    if (m_directionChangeClock.getElapsedTime() >= m_randomChangeInterval) {
        randomizeBehavior();
        m_directionChangeClock.restart();
    }
}

void SmartGuard::handleCollisionWith(Bomb&, bool isExploding) {
    
    getRevert();
    setVelocity(-getVelocity()); 
    randomizeBehavior(); 
}

void SmartGuard::handleCollisionWith(Guard&) {

}
sf::CircleShape SmartGuard::getCollisionShape() const {
    sf::CircleShape collisionEllipse;

    float radiusX = getFrameWidth() / 4;  
    float radiusY = getFrameHight() / 6; 
    collisionEllipse.setRadius(radiusX); 

    // Scale it horizontally to form an ellipse
    float horizontalScale = 0.7f;  
    float verticalScale = 1.f;   
    collisionEllipse.setScale(horizontalScale, verticalScale);
    collisionEllipse.setPosition(
        getPosition().x + getFrameWidth() / 2 - (5 * CIRCLRE_OFFSET),
        getPosition().y + getFrameHight() / 2 - (7 * CIRCLRE_OFFSET)
    );

    return collisionEllipse;
}

void SmartGuard::updateVelocity(Direction dir) {
    
    switch (dir) {
    case UP:    setVelocity({ 0.f, -m_speed }); break;
    case DOWN:  setVelocity({ 0.f, m_speed }); break;
    case LEFT: setVelocity({ -m_speed, 0.f }); break;
    case RIGHT: setVelocity({ m_speed, 0.f }); break;
    }
}
