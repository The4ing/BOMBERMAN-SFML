#include "StupidGuard.h"
#include <iostream>

// Constants
const float GUARD_SPEED = 500.f;   // Speed in pixels per second
const int SPRITE_COLUMNS = 3;      // Number of frames per row
const int SPRITE_ROWS = 4;         // Number of directional rows
const float GUARD_SCALE = 1.f;    // Scale factor
const float GUARD_CHANGE_INTERVAL = 2.f;  // Increase the interval


StupidGuard::StupidGuard()
    : m_randomChangeInterval(sf::seconds(GUARD_CHANGE_INTERVAL)) , m_animationFrame(0){
    // Load sprite sheet

    if (!m_texture.loadFromFile("scary_guard_spritesheet.png")) {
        std::cerr << "Failed to load guard spritesheet" << std::endl;
    }

    // Set up the sprite
    m_sprite.setTexture(m_texture);

    // Calculate frame dimensions
    m_frameWidth = 127.5f;
    m_frameHeight = 163.3f;

    // Set the initial texture rectangle (first frame of the first row)
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    m_sprite.setScale(1.f, 1.f); // Scale as needed
    // Initialize random direction
    changeDirection();
}

void StupidGuard::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::Vector2f StupidGuard::getPosition() const {
    return m_sprite.getPosition();
}

void StupidGuard::update(const float deltaTime) {

    const float SpeedMove = deltaTime * 0.7;
    // Increase the time since the last direction change
    m_timeSinceLastChange += sf::seconds(SpeedMove);

     
    // Move the guard
    m_sprite.move(m_velocity * SpeedMove);
    // Only change direction if the cooldown period has passed
    if (m_timeSinceLastChange >= m_randomChangeInterval) {
        changeDirection();
        m_timeSinceLastChange = sf::Time::Zero;  // Reset the timer
    }

    // Animation frame update with a cooldown to prevent flickering
    m_animationTimeSinceLastChange += sf::seconds(SpeedMove);
    if (m_animationTimeSinceLastChange >= sf::milliseconds(100)) {
        m_animationFrame = (m_animationFrame + 1) % 4;
        m_animationTimeSinceLastChange = sf::Time::Zero;  // Reset the timer
    }

    int textureX = m_animationFrame * m_frameWidth; // Horizontal frame index

    // Determine textureY based on the guard's direction
    int textureY = 0;
    if (m_direction == DOWN) {
        textureY = 0; // First row for moving down
        m_sprite.setScale(GUARD_SCALE, GUARD_SCALE); // Reset scale
        m_sprite.setOrigin(0.f, 0.f); // Reset origin
    }
    else if (m_direction == LEFT) {
        textureY = m_frameHeight; // Second row for moving left
        m_sprite.setScale(GUARD_SCALE, GUARD_SCALE); // Reset scale
        m_sprite.setOrigin(0.f, 0.f); // Reset origin
    }
    else if (m_direction == RIGHT) {
        textureY = m_frameHeight; // Second row for moving right
        m_sprite.setScale(-GUARD_SCALE, GUARD_SCALE); // Invert the sprite horizontally
        m_sprite.setOrigin(m_frameWidth, 0.f); // Adjust origin to align correctly
    }
    else if (m_direction == UP) {
        textureY = m_frameHeight * 2; // Third row for moving up
        m_sprite.setScale(GUARD_SCALE, GUARD_SCALE); // Reset scale
        m_sprite.setOrigin(0.f, 0.f); // Reset origin
    }

    // Apply texture to sprite
    m_sprite.setTextureRect(sf::IntRect(textureX, textureY, m_frameWidth, m_frameHeight));
}



void StupidGuard::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
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








