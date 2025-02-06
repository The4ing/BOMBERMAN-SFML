#include "StupidGuard.h"
#include <iostream>

// Constants
const float GUARD_SPEED = 100.f;   // Speed in pixels per second
const int SPRITE_COLUMNS = 3;      // Number of frames per row
const int SPRITE_ROWS = 4;         // Number of directional rows
const float GUARD_SCALE = 1.f;    // Scale factor
const float GUARD_CHANGE_INTERVAL = 2.f;  // Interval to change direction

StupidGuard::StupidGuard()
    : m_randomChangeInterval(sf::seconds(GUARD_CHANGE_INTERVAL))
    
{
    ResourceManager& resourceManager = ResourceManager::getInstance();

    // Set up the sprite
  
    sf::Sprite& sprite = getSprite();

    sprite.setTexture(resourceManager.getTexture("scary_guard_spritesheet.png"));

    // Set the initial texture rectangle (first frame of the first row)
    sprite.setTextureRect(sf::IntRect(0, 0, getFrameWidth(), getFrameHight()));


    // m_sprite.setOrigin(m_frameWidth / 2, m_frameHeight / 2);

     // Initialize random direction
    changeDirection();
}






void StupidGuard::changeDirection() {
    // Random direction generator
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> distribution(1, SPRITE_ROWS);

    // Set a new direction
    m_direction = static_cast<Direction>(distribution(generator));

    // Update velocity based on direction
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


    // Save the current position before moving
    setPrevPpos(getPosition());

    // Increase the time since the last direction change
    m_timeSinceLastChange += sf::seconds(deltaTime);

    // Move the guard
    spriteGurad.move(getVelocity() * deltaTime);

    // Change direction if the cooldown period has passed
    if (m_timeSinceLastChange >= m_randomChangeInterval) {
        changeDirection();
        m_timeSinceLastChange = sf::Time::Zero;  // Reset the timer
    }

    // Animation frame update with a cooldown to prevent flickering
    m_animationTimeSinceLastChange += sf::seconds(deltaTime);
    if (m_animationTimeSinceLastChange >= sf::milliseconds(100)) {
        setAnimation((getAnimation() + 1) % 4);
        m_animationTimeSinceLastChange = sf::Time::Zero;  // Reset the timer
    }

    // Determine the current animation frame and texture rectangle
    int textureX = getAnimation() * getFrameWidth();
    int textureY = 0;

    if (m_direction == DOWN) {
        textureY = 0;
        //m_sprite.setOrigin(0.f, 0.f);
    }
    else if (m_direction == LEFT) {
        textureY = static_cast<int>(getFrameHight());
        //  m_sprite.setOrigin(0.f, 0.f);
    }
    else if (m_direction == RIGHT) {
        textureY = static_cast<int>(getFrameHight());
        // m_sprite.setOrigin(m_frameWidth, 0.f);
    }
    else if (m_direction == UP) {
        textureY = static_cast<int>(getFrameHight() * 2);
        // m_sprite.setOrigin(0.f, 0.f);
    }

    spriteGurad.setTextureRect(sf::IntRect(textureX, textureY, getFrameWidth(), getFrameHight()));
}










//void StupidGuard::handleCollisionWith(Wall& ) {
//
//    getRevert();
//}



void StupidGuard::handleCollisionWith(Bomb&, bool) {
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




