#include "Robot.h"
#include <iostream>
#include <set>

// Constructor
Robot::Robot()
    : m_direction(STAND),
    m_arrowKeyPressed(false),
    m_animationFrame(0),
    m_animationTimer(sf::milliseconds(100))
{
    if (!m_texture.loadFromFile("robot_spritesheet.png")) {
        std::cerr << "Failed to load robot spritesheet" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(4 * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
    m_sprite.setScale(ROBOT_SCALE, ROBOT_SCALE);
}

// Position handling
void Robot::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::Vector2f Robot::getPosition() const {
    return m_sprite.getPosition();
}

sf::Vector2i Robot::getCurrentCell() const {
    sf::Vector2f pos = m_sprite.getPosition();
    return sf::Vector2i(
        static_cast<int>(pos.x / (SPRITE_WIDTH * ROBOT_SCALE)),
        static_cast<int>(pos.y / (SPRITE_HEIGHT * ROBOT_SCALE))
    );
}

void Robot::update(float deltaTime) {
    // Update the position based on velocity and deltaTime
    m_sprite.move(m_velocity * deltaTime);

    // Calculate and store the current cell position
    sf::Vector2f spritePosition = m_sprite.getPosition();

    // Check if the robot is supposed to be "dead"
    if (/* condition for death */ false) { // Replace false with your actual death condition
        // Handle dead animation (second row in the sprite sheet)
        int deadFrame = (m_animationClock.getElapsedTime().asMilliseconds() / 100) % 7; // Assume 7 frames for "dead"
        m_sprite.setTextureRect(sf::IntRect(deadFrame * SPRITE_WIDTH, SPRITE_HEIGHT * 4, SPRITE_WIDTH, SPRITE_HEIGHT));
        return; // Skip normal animation if dead
    }

    // Handle animation updates for movement
    if (m_arrowKeyPressed) {
        if (m_animationClock.getElapsedTime() > m_animationTimer) {
            // Advance to the next frame
            m_animationFrame = (m_animationFrame + 1) % 3; // 3 frames per direction

            // Determine the sprite sheet coordinates for the animation
            int textureX = (m_animationFrame + ((m_direction - 1) * 3)) * SPRITE_WIDTH;              // Horizontal frame index
            int textureY = 0;                                           // Always use the first row for all directions
            m_sprite.setTextureRect(sf::IntRect(textureX, textureY, SPRITE_WIDTH, SPRITE_HEIGHT));

            m_animationClock.restart(); // Reset the animation timer
        }
    }
    else {
        // If the robot is not moving, reset to the first frame of the standing animation
        switch (lastDirection) {
        case UP:
            m_sprite.setTextureRect(sf::IntRect(7 * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
            break;
        case DOWN:
            m_sprite.setTextureRect(sf::IntRect(4 * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
            break;
        case LEFT:
            m_sprite.setTextureRect(sf::IntRect(1 * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
            break;
        case RIGHT:
            m_sprite.setTextureRect(sf::IntRect(10 * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
            break;
        default:
            break;
        }
    }
}
void Robot::handleInput(sf::Keyboard::Key key, bool isPressed) {
    static std::set<sf::Keyboard::Key> activeKeys;

    if (isPressed) {
        lastDirection = m_direction;
        // Add the key to the set
        activeKeys.insert(key);

        // Update movement direction and velocity based on the active key
        if (activeKeys.count(sf::Keyboard::Up) && !activeKeys.count(sf::Keyboard::Down)) {
            m_velocity.y = -ROBOT_SPEED;
            m_velocity.x = 0.f;
            m_direction = UP;
        }
        else if (activeKeys.count(sf::Keyboard::Down) && !activeKeys.count(sf::Keyboard::Up)) {
            m_velocity.y = ROBOT_SPEED;
            m_velocity.x = 0.f;
            m_direction = DOWN;
        }
        else if (activeKeys.count(sf::Keyboard::Left) && !activeKeys.count(sf::Keyboard::Right)) {
            m_velocity.x = -ROBOT_SPEED;
            m_velocity.y = 0.f;
            m_direction = LEFT;
        }
        else if (activeKeys.count(sf::Keyboard::Right) && !activeKeys.count(sf::Keyboard::Left)) {
            m_velocity.x = ROBOT_SPEED;
            m_velocity.y = 0.f;
            m_direction = RIGHT;
        }
    }
    else {
        // Remove the key from the set
        activeKeys.erase(key);

        // Reset velocity and direction if no active keys remain
        if (activeKeys.empty()) {
            m_velocity = { 0.f, 0.f };
            m_direction = STAND;
            m_arrowKeyPressed = false;
        }
        else {
            // Handle remaining active keys (resolving conflicts)
            if (activeKeys.count(sf::Keyboard::Up) && !activeKeys.count(sf::Keyboard::Down)) {
                m_velocity.y = -ROBOT_SPEED;
                m_velocity.x = 0.f;
                m_direction = UP;
            }
            else if (activeKeys.count(sf::Keyboard::Down) && !activeKeys.count(sf::Keyboard::Up)) {
                m_velocity.y = ROBOT_SPEED;
                m_velocity.x = 0.f;
                m_direction = DOWN;
            }
            else if (activeKeys.count(sf::Keyboard::Left) && !activeKeys.count(sf::Keyboard::Right)) {
                m_velocity.x = -ROBOT_SPEED;
                m_velocity.y = 0.f;
                m_direction = LEFT;
            }
            else if (activeKeys.count(sf::Keyboard::Right) && !activeKeys.count(sf::Keyboard::Left)) {
                m_velocity.x = ROBOT_SPEED;
                m_velocity.y = 0.f;
                m_direction = RIGHT;
            }
            else {
                // If conflicting keys are pressed, stop movement
                m_velocity = { 0.f, 0.f };
                m_direction = STAND;
            }
        }
    }

    m_arrowKeyPressed = !activeKeys.empty();
}

// Draw method
void Robot::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}
