#include "SmartGuard.h"
#include <cmath> // For sqrt and pow
#include <iostream> // For logging

SmartGuard::SmartGuard()
    : m_speed(200.f),
    m_randomChangeInterval(sf::seconds(3.f)),
    m_animationFrame(0),
    m_frameWidth(127.5f), // Frame width based on your sprite sheet
    m_frameHeight(163.3f) // Frame height based on your sprite sheet
{
    // Load the sprite sheet
    if (!m_texture.loadFromFile("smartGuardSprite.png")) {
        std::cerr << "Failed to load guard sprite sheet" << std::endl;
    }

    // Setup the sprite
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, m_frameWidth, m_frameHeight));
    m_sprite.setScale(1.f, 1.f); // Scale as needed

    // Randomize initial behavior
    randomizeBehavior();
}

void SmartGuard::setPosition(float newX, float newY) {
    m_sprite.setPosition(newX, newY);
}

sf::Vector2f SmartGuard::getPosition() const {
    return m_sprite.getPosition();
}

void SmartGuard::setPlayerPosition(const sf::Vector2f& playerPos) {
    m_playerPosition = playerPos;
}







void SmartGuard::update(const float deltaTime ) {

    const float SpeedMove = deltaTime * 0.5;
    
    // Continuously calculate velocity toward the player
    calculateVelocity();

    // Move the guard
    m_sprite.move(m_velocity * SpeedMove);

    // Check if it's time to randomize behavior
    if (m_directionChangeClock.getElapsedTime() >= m_randomChangeInterval) {
        randomizeBehavior();
        m_directionChangeClock.restart();
    }

    // Update animation
    updateAnimation();
}

void SmartGuard::calculateVelocity() {
    // Calculate direction vector toward the player
    sf::Vector2f direction = m_playerPosition - m_sprite.getPosition();

    // Normalize the vector
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0) {
        direction /= magnitude; // Normalize
    }

    // Scale by speed
    m_velocity = direction * m_speed;
}

void SmartGuard::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void SmartGuard::handleInput(sf::Keyboard::Key key, bool isPressed) {
    // For future use, e.g., player influencing guard behavior
}

void SmartGuard::randomizeBehavior() {
    static std::default_random_engine generator;
    static std::uniform_real_distribution<float> intervalDist(2.f, 5.f);

    // Randomize next direction change interval
    m_randomChangeInterval = sf::seconds(intervalDist(generator));

    // Optional: Add slight random offset to velocity for unpredictable movement
    static std::uniform_real_distribution<float> offsetDist(-50.f, 50.f);
    m_velocity.x += offsetDist(generator);
    m_velocity.y += offsetDist(generator);
}

void SmartGuard::updateAnimation() {
    // Advance the animation frame every 100ms
    if (m_animationClock.getElapsedTime() >= sf::milliseconds(100)) {
        m_animationFrame = (m_animationFrame + 1) % 4; // Assuming 4 frames per direction
        m_animationClock.restart();
    }

    // Determine texture rect based on direction and animation frame
    int textureX = m_animationFrame * m_frameWidth;
    int textureY = 0;

    if (m_velocity.y > 0) { // Moving down
        textureY = 0; // First row
        m_sprite.setScale(1.f, 1.f);
    }
    else if (m_velocity.y < 0) { // Moving up
        textureY = m_frameHeight * 2; // Third row
        m_sprite.setScale(1.f, 1.f);
    }
    else if (m_velocity.x > 0) { // Moving right
        textureY = m_frameHeight; // Second row
        m_sprite.setScale(1.f, 1.f);
    }
    else if (m_velocity.x < 0) { // Moving left
        textureY = m_frameHeight; // Second row
        m_sprite.setScale(-1.f, 1.f); // Flip sprite horizontally
    }

    // Update the sprite's texture rectangle
    m_sprite.setTextureRect(sf::IntRect(textureX, textureY, m_frameWidth, m_frameHeight));
}









