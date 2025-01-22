#include "Robot.h"
#include <iostream>

Robot::Robot()
    : m_direction(STAND),
    m_arrowKeyPressed(false),
    m_animationFrame(0),
    m_animationTimer(sf::milliseconds(100)) // Frame duration: 100ms
{
    // Load the texture from the spritesheet
    if (!m_texture.loadFromFile("robot_spritesheet.png")) {
        std::cerr << "Failed to load robot spritesheet" << std::endl;
    }

    // Set up the sprite
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
    m_sprite.setScale(ROBOT_SCALE, ROBOT_SCALE);
}

void Robot::setPosition(float x, float y) {
    m_sprite.setPosition(x, y); // Set the sprite's position
}

sf::Vector2f Robot::getPosition() const {
    return m_sprite.getPosition(); // Return the sprite's position
}

sf::Vector2i Robot::getCurrentCell() const {
    // Calculate the current cell dynamically based on sprite position
    sf::Vector2f pos = m_sprite.getPosition();
    return sf::Vector2i(
        static_cast<int>(pos.x / (SPRITE_WIDTH * ROBOT_SCALE)),
        static_cast<int>(pos.y / (SPRITE_HEIGHT * ROBOT_SCALE))
    );
}

void Robot::update(float deltaTime) {
    // Move the sprite dynamically based on its direction
    float distance = ROBOT_SPEED * deltaTime;

    switch (m_direction) {
    case UP:
        m_sprite.move(0, -distance);
        break;
    case DOWN:
        m_sprite.move(0, distance);
        break;
    case LEFT:
        m_sprite.move(-distance, 0);
        break;
    case RIGHT:
        m_sprite.move(distance, 0);
        break;
    default:
        break;
    }

    // Handle animation updates
    if (m_arrowKeyPressed && m_animationClock.getElapsedTime() > m_animationTimer) {
        m_animationFrame = (m_animationFrame + 1) % 3; // 3 frames per direction
        int textureX = (m_animationFrame + ((m_direction - 1) * 3)) * SPRITE_WIDTH;
        m_sprite.setTextureRect(sf::IntRect(textureX, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
        m_animationClock.restart();
    }
}

void Robot::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (isPressed) {
        switch (key) {
        case sf::Keyboard::Up:
            m_direction = UP;
            m_arrowKeyPressed = true;
            break;
        case sf::Keyboard::Down:
            m_direction = DOWN;
            m_arrowKeyPressed = true;
            break;
        case sf::Keyboard::Left:
            m_direction = LEFT;
            m_arrowKeyPressed = true;
            break;
        case sf::Keyboard::Right:
            m_direction = RIGHT;
            m_arrowKeyPressed = true;
            break;
        default:
            break;
        }
    }
    else {
        // Stop movement and reset direction to STAND
        m_arrowKeyPressed = false;
        m_direction = STAND;
    }
}

void Robot::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}
