#include "Robot.h"
#include <iostream>

// Starting position for the robot
const sf::Vector2f START_POSITION(100.f, 100.f);

Robot::Robot()
    : m_velocity(0.f, 0.f),
    m_direction(STAND),
    m_arrowKeyPressed(false),
    m_animationFrame(0),
    m_animationTimer(sf::milliseconds(100)) // Each frame lasts 100ms
{
    // Load the texture from the spritesheet file
    if (!m_texture.loadFromFile("robot_spritesheet.png")) {
        std::cerr << "Failed to load robot spritesheet" << std::endl;
    }

    // Set up the sprite
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
    m_sprite.setPosition(START_POSITION);
    m_sprite.setScale(ROBOT_SCALE, ROBOT_SCALE);
}

void Robot::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::Vector2f Robot::getPosition() const {
    return m_sprite.getPosition();
}

void Robot::setVelocity(float vx, float vy) {
    m_velocity.x = vx;
    m_velocity.y = vy;
}

void Robot::update(float deltaTime) {
    // Update the position based on velocity and deltaTime
    m_sprite.move(m_velocity * deltaTime);

    // Check if the robot is supposed to be "dead"
    if (/* condition for death */ false) { // Replace `false` with your actual death condition
        // Handle dead animation (second row in the sprite sheet)
        int deadFrame = (m_animationClock.getElapsedTime().asMilliseconds() / 100) % 7; // 3 frames for dead
        m_sprite.setTextureRect(sf::IntRect(deadFrame * SPRITE_WIDTH, SPRITE_HEIGHT * 4, SPRITE_WIDTH, SPRITE_HEIGHT));
        return; // Skip normal animation if dead
    }

    // Handle normal animation updates for movement
    if (m_arrowKeyPressed && m_animationClock.getElapsedTime() > m_animationTimer) {
        // Advance to the next frame
        m_animationFrame = (m_animationFrame + 1) % 3; // 3 frames per direction

        // Determine the sprite sheet coordinates for the animation
        std::cout << m_direction << " and " << m_animationFrame << std::endl;
        int textureX =  (m_animationFrame + ((m_direction - 1) * 3)) * SPRITE_WIDTH;              // Horizontal frame index
        int textureY = 0;                                           // Always use the first row for all directions
        m_sprite.setTextureRect(sf::IntRect(textureX, textureY, SPRITE_WIDTH, SPRITE_HEIGHT));

        m_animationClock.restart(); // Reset the animation timer
    }


}


void Robot::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

void Robot::handleInput(sf::Keyboard::Key key, bool isPressed) {
    // Handle keyboard inputs and set velocity/direction
    switch (key) {
    case sf::Keyboard::Up:
        m_velocity.y = isPressed ? -ROBOT_SPEED : 0.f;
        m_direction = isPressed ? UP : STAND;
        break;
    case sf::Keyboard::Down:
        m_velocity.y = isPressed ? ROBOT_SPEED : 0.f;
        m_direction = isPressed ? DOWN : STAND;
        break;
    case sf::Keyboard::Left:
        m_velocity.x = isPressed ? -ROBOT_SPEED : 0.f;
        m_direction = isPressed ? LEFT : STAND;
        break;
    case sf::Keyboard::Right:
        m_velocity.x = isPressed ? ROBOT_SPEED : 0.f;
        m_direction = isPressed ? RIGHT : STAND;
        break;
    default:
        break;
    }
    m_arrowKeyPressed = isPressed; // Update arrow key state
}
