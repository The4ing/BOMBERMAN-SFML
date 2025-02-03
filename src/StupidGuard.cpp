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
    sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));


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
        m_velocity = { 0.f, -GUARD_SPEED };
        break;
    case DOWN:
        m_velocity = { 0.f, GUARD_SPEED };
        break;
    case LEFT:
        m_velocity = { -GUARD_SPEED, 0.f };
        break;
    case RIGHT:
        m_velocity = { GUARD_SPEED, 0.f };
        break;
    default:
        break;
    }
}

void StupidGuard::update(float deltaTime) {

    sf::Sprite& spriteGurad = getSprite();


    // Save the current position before moving
    m_previousPosition = getPosition();

    // Increase the time since the last direction change
    m_timeSinceLastChange += sf::seconds(deltaTime);

    // Move the guard
    spriteGurad.move(m_velocity * deltaTime);

    // Change direction if the cooldown period has passed
    if (m_timeSinceLastChange >= m_randomChangeInterval) {
        changeDirection();
        m_timeSinceLastChange = sf::Time::Zero;  // Reset the timer
    }

    // Animation frame update with a cooldown to prevent flickering
    m_animationTimeSinceLastChange += sf::seconds(deltaTime);
    if (m_animationTimeSinceLastChange >= sf::milliseconds(100)) {
        m_animationFrame = (m_animationFrame + 1) % 4;
        m_animationTimeSinceLastChange = sf::Time::Zero;  // Reset the timer
    }

    // Determine the current animation frame and texture rectangle
    int textureX = m_animationFrame * m_frameWidth;
    int textureY = 0;

    if (m_direction == DOWN) {
        textureY = 0;
        //m_sprite.setOrigin(0.f, 0.f);
    }
    else if (m_direction == LEFT) {
        textureY = static_cast<int>(m_frameHeight);
        //  m_sprite.setOrigin(0.f, 0.f);
    }
    else if (m_direction == RIGHT) {
        textureY = static_cast<int>(m_frameHeight);
        // m_sprite.setOrigin(m_frameWidth, 0.f);
    }
    else if (m_direction == UP) {
        textureY = static_cast<int>(m_frameHeight * 2);
        // m_sprite.setOrigin(0.f, 0.f);
    }

    spriteGurad.setTextureRect(sf::IntRect(textureX, textureY, m_frameWidth, m_frameHeight));
}










void StupidGuard::handleCollisionWith(Wall& wall) {

    revertPosition();
}








void StupidGuard::handleCollisionWith(Bomb&, bool) {
    revertPosition();
}



sf::CircleShape StupidGuard::getCollisionShape() const {
    sf::CircleShape collisionShape;
    float radius = static_cast<float>(m_frameWidth / 6);  // Adjust the radius
    collisionShape.setRadius(radius);
    collisionShape.setOrigin(radius, radius);  // Center the circle

    // Position the circle
    collisionShape.setPosition(
        getPosition().x + m_frameWidth / 2 - (3 * CIRCLRE_OFFSET),
        getPosition().y + m_frameHeight / 2 - (3 * CIRCLRE_OFFSET)
    );

    return collisionShape;
}




