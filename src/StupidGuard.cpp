#include "StupidGuard.h"
#include <iostream>

// Constants
const float GUARD_SPEED = 500.f;   // Speed in pixels per second
const int SPRITE_COLUMNS = 3;      // Number of frames per row
const int SPRITE_ROWS = 4;         // Number of directional rows
const float GUARD_SCALE = 1.f;    // Scale factor
const float GUARD_CHANGE_INTERVAL = 2.f;  // Interval to change direction

StupidGuard::StupidGuard()
    : m_randomChangeInterval(sf::seconds(GUARD_CHANGE_INTERVAL)), m_animationFrame(0), m_previousPosition(0.f, 0.f) {
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
   // m_sprite.setOrigin(m_frameWidth / 2, m_frameHeight / 2);

    // Initialize random direction
    changeDirection();
}

void StupidGuard::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

sf::Vector2f StupidGuard::getPosition() const {
    return m_sprite.getPosition();
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
    // Save the current position before moving
    m_previousPosition = m_sprite.getPosition();

    // Increase the time since the last direction change
    m_timeSinceLastChange += sf::seconds(deltaTime);

    // Move the guard
    m_sprite.move(m_velocity * deltaTime);

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
        textureY = m_frameHeight;
      //  m_sprite.setOrigin(0.f, 0.f);
    }
    else if (m_direction == RIGHT) {
        textureY = m_frameHeight;
       // m_sprite.setOrigin(m_frameWidth, 0.f);
    }
    else if (m_direction == UP) {
        textureY = m_frameHeight * 2;
       // m_sprite.setOrigin(0.f, 0.f);
    }

    m_sprite.setTextureRect(sf::IntRect(textureX, textureY, m_frameWidth, m_frameHeight));
}




void StupidGuard::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
    sf::CircleShape collisionShape = getCollisionShape();
    collisionShape.setFillColor(sf::Color::Transparent);
    collisionShape.setOutlineColor(sf::Color::Red);
    collisionShape.setOutlineThickness(1.f);
    window.draw(collisionShape);
}


void StupidGuard::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}

sf::FloatRect StupidGuard::getBoundingBox() const {
    return m_sprite.getGlobalBounds();
}

void StupidGuard::handleCollisionWith(Wall& wall) {

        revertPosition();
}

void StupidGuard::handleCollisionWith(Rock& rock) {

        revertPosition();
}

void StupidGuard::handleCollisionWith(Door&) {
    std::cout << "StupidGuard collided with Door.\n";
}
void StupidGuard::handleCollisionWith(Robot&) {
    std::cout << "StupidGuard collided with Door.\n";
}


void StupidGuard::handleCollisionWith(Guard&) {
    std::cout << "StupidGuard collided with another Guard.\n";
}
void StupidGuard::handleCollisionWith(Bomb&, bool isExploding) {
      revertPosition();
}

void StupidGuard::revertPosition() {
    m_sprite.setPosition(m_previousPosition);
}

void StupidGuard::setScale(float scaleX, float scaleY) {
    m_sprite.setScale(scaleX, scaleY);
}

sf::CircleShape StupidGuard::getCollisionShape() const {
    sf::CircleShape collisionEllipse;
    float radiusX = m_frameWidth / 4;  // Horizontal radius (adjust as needed)
    float radiusY = m_frameHeight / 6; // Vertical radius (adjust as needed)

    collisionEllipse.setRadius(radiusX);  // Base radius (use the larger dimension)
    // Scale it horizontally to form an ellipse
    float horizontalScale = 0.7f;  // Adjust this value for width
    float verticalScale = 1.f;    // Keep this 1.0 to maintain original height
    collisionEllipse.setScale(horizontalScale, verticalScale);

  //  collisionEllipse.setOrigin(radiusX, radiusX);  // Origin remains at center
    collisionEllipse.setPosition(
        m_sprite.getPosition().x + m_frameWidth / 2 - (5 * CIRCLRE_OFFSET),
        m_sprite.getPosition().y + m_frameHeight / 2 - (6 * CIRCLRE_OFFSET)
    );

    return collisionEllipse;
}


void StupidGuard::setStartingPosition(float newX, float newY) {
    m_startingPosition = sf::Vector2f(newX, newY);
}
sf::Vector2f StupidGuard::getStartingPosition() {
    return m_startingPosition;
}
