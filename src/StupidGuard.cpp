#include "StupidGuard.h"
#include <iostream>

StupidGuard::StupidGuard()
    : m_randomChangeInterval(sf::seconds(GUARD_CHANGE_INTERVAL))
    
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sprite& sprite = getSprite();
    sprite.setTexture(resourceManager.getTexture("scary_guard_spritesheet.png"));
    sprite.setTextureRect(sf::IntRect(0, 0, getFrameWidth(), getFrameHight()));
    changeDirection();
}

void StupidGuard::changeDirection() {
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(1, SPRITE_ROWS);
    m_direction = static_cast<Direction>(distribution(generator));

    switch (m_direction) {
    case UP:
        setVelocity({ 0.f, -GUARD_SPEED });
        break;
    case DOWN:
        setVelocity({ 0.f, GUARD_SPEED });
        break;
    case LEFT:
        setVelocity({ -GUARD_SPEED, 0.f });
        break;
    case RIGHT:
        setVelocity({ GUARD_SPEED, 0.f });
        break;
    default:
        break;
    }
}

void StupidGuard::update(float deltaTime) {

    sf::Sprite& spriteGurad = getSprite();
    setPrevPpos(getPosition());
    m_timeSinceLastChange += sf::seconds(deltaTime);

    spriteGurad.move(getVelocity() * deltaTime);

    if (m_timeSinceLastChange >= m_randomChangeInterval) {
        changeDirection();
        m_timeSinceLastChange = sf::Time::Zero;
    }
    m_animationTimeSinceLastChange += sf::seconds(deltaTime);
    if (m_animationTimeSinceLastChange >= sf::milliseconds(100)) {
        setAnimation((getAnimation() + 1) % 4);
        m_animationTimeSinceLastChange = sf::Time::Zero;
    }
    int textureX = getAnimation() * getFrameWidth();
    int textureY = 0;

    if (m_direction == DOWN) {
        textureY = 0;
    }
    else if (m_direction == LEFT) {
        textureY = static_cast<int>(getFrameHight());
    }
    else if (m_direction == RIGHT) {
        textureY = static_cast<int>(getFrameHight());
    }
    else if (m_direction == UP) {
        textureY = static_cast<int>(getFrameHight() * 2);
    }

    spriteGurad.setTextureRect(sf::IntRect(textureX, textureY, getFrameWidth(), getFrameHight()));
}
void StupidGuard::handleCollisionWith(Bomb&, bool isExploding) {
    getRevert();
}

sf::CircleShape StupidGuard::getCollisionShape() const {
    sf::CircleShape collisionShape;
    float radius = static_cast<float>(getFrameWidth() / 6);  // Adjust the radius
    collisionShape.setRadius(radius);
    collisionShape.setOrigin(radius, radius);  // Center the circle

    // Position the circle
    collisionShape.setPosition(
        getPosition().x + getFrameWidth() / 2 - (3 * CIRCLRE_OFFSET),
        getPosition().y + getFrameHight() / 2 - (3 * CIRCLRE_OFFSET)
    );

    return collisionShape;
}
