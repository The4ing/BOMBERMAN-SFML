#include "SmartGuard.h"
#include <cmath>
#include <iostream>

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
   // m_sprite.setScale(1.f, 1.f); // Scale as needed

    // Randomize initial behavior
    randomizeBehavior();
}

void SmartGuard::setPosition(float newX, float newY) {
    m_sprite.setPosition(newX, newY);
}
void SmartGuard::setStartingPosition(float newX, float newY) {
    m_startingPosition = sf::Vector2f(newX, newY);
}
sf::Vector2f SmartGuard::getStartingPosition() {
    return m_startingPosition;
}

sf::Vector2f SmartGuard::getPosition() const {
    return m_sprite.getPosition();
}

void SmartGuard::setPlayerPosition(const sf::Vector2f& playerPos) {
    m_playerPosition = playerPos;
}

void SmartGuard::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
    sf::CircleShape collisionShape = getCollisionShape();
    collisionShape.setFillColor(sf::Color::Transparent);
    collisionShape.setOutlineColor(sf::Color::Red);
    collisionShape.setOutlineThickness(1.f);
    window.draw(collisionShape);
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

void SmartGuard::calculateVelocity() {
    sf::Vector2f direction = m_playerPosition - m_sprite.getPosition();
    float distanceX = std::abs(direction.x);
    float distanceY = std::abs(direction.y);

    // Store preferred movement
    if (distanceX > distanceY) {
        preferredDirection = (direction.x > 0) ? RIGHT : LEFT;
        alternateDirection = (direction.y > 0) ? DOWN : UP;
    }
    else {
        preferredDirection = (direction.y > 0) ? DOWN : UP;
        alternateDirection = (direction.x > 0) ? RIGHT : LEFT;
    }

    // Apply velocity based on preferred direction
    setVelocity(preferredDirection);
}



void SmartGuard::updateAnimation() {
    // Advance the animation frame every 100ms
    if (m_animationClock.getElapsedTime() >= sf::milliseconds(100)) {
        m_animationFrame = (m_animationFrame + 1) % 4;
        m_animationClock.restart();
    }

    // Determine texture row based on movement direction
    int textureX = m_animationFrame * m_frameWidth;
    int textureY = 0;

    if (m_velocity.y > 0) {
        textureY = 0;  // Moving down
    }
    else if (m_velocity.y < 0) {
        textureY = m_frameHeight * 2;  // Moving up
    }
    else if (m_velocity.x > 0) {
        textureY = m_frameHeight;  // Moving right
    }
    else if (m_velocity.x < 0) {
        textureY = m_frameHeight;  // Moving left
    }

    m_sprite.setTextureRect(sf::IntRect(textureX, textureY, m_frameWidth, m_frameHeight));
}


void SmartGuard::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}

void SmartGuard::handleCollisionWith(Robot& robot) {
    std::cout << "SmartGuard collided with Robot: Initiate chase logic!\n";
}

void SmartGuard::handleCollisionWith(Wall&) {
    std::cout << "SmartGuard hit a wall! Changing direction.\n";

    if (m_velocity.x != 0 || m_velocity.y != 0) {
        // First, switch to alternate direction
        setVelocity(alternateDirection);
    }
    else {
        // If alternate direction is also blocked, try random direction
        moveInAnyAvailableDirection();
    }
}


void SmartGuard::handleCollisionWith(Rock&) {
    revertPosition();
}

void SmartGuard::handleCollisionWith(Door&) {
    revertPosition();
}

void SmartGuard::handleCollisionWith(Bomb&, bool isExploding) {
    std::cout << "SmartGuard collided with Bomb: Reverting position and avoiding bomb.\n";

    // Revert position
    revertPosition();

    // Adjust velocity to move away from the bomb
    m_velocity = -m_velocity; // Reverse direction
    randomizeBehavior();      // Optionally randomize behavior to avoid getting stuck
}

void SmartGuard::handleCollisionWith(Guard&) {
    std::cout << "SmartGuard collided with another Guard.\n";
    m_velocity = sf::Vector2f(0.f, 0.f);
}

sf::FloatRect SmartGuard::getBoundingBox() const {
    return m_sprite.getGlobalBounds();
}

void SmartGuard::setScale(float scaleX, float scaleY) {
    m_sprite.setScale(scaleX, scaleY);
}

void SmartGuard::revertPosition() {
    m_sprite.setPosition(m_previousPosition);
}

sf::CircleShape SmartGuard::getCollisionShape() const {
    sf::CircleShape collisionShape;
    float radius = m_frameWidth / 4;  // Adjust the radius
    collisionShape.setRadius(radius);
    collisionShape.setOrigin(radius, radius);  // Center the circle

    // Position the circle
    collisionShape.setPosition(
        m_sprite.getPosition().x + m_frameWidth / 2 - CIRCLRE_OFFSET,
        m_sprite.getPosition().y + m_frameHeight / 2 - CIRCLRE_OFFSET
    );

    return collisionShape;
}

void SmartGuard::setVelocity(Direction dir) {
    switch (dir) {
    case UP:    m_velocity = { 0.f, -m_speed }; break;
    case DOWN:  m_velocity = { 0.f, m_speed }; break;
    case LEFT:  m_velocity = { -m_speed, 0.f }; break;
    case RIGHT: m_velocity = { m_speed, 0.f }; break;
    }
}

void SmartGuard::update(float deltaTime) {
    m_previousPosition = m_sprite.getPosition();

    calculateVelocity();
    m_sprite.move(m_velocity * deltaTime);

    updateAnimation();

    if (m_directionChangeClock.getElapsedTime() >= m_randomChangeInterval) {
        randomizeBehavior();
        m_directionChangeClock.restart();
    }
}

void SmartGuard::moveInAnyAvailableDirection() {
    std::vector<Direction> possibleDirections = { UP, DOWN, LEFT, RIGHT };
    std::shuffle(possibleDirections.begin(), possibleDirections.end(), std::mt19937(std::random_device()()));

    for (Direction dir : possibleDirections) {
        setVelocity(dir);
        break;
    }
}
