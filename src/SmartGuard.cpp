#include "SmartGuard.h"
#include <cmath>
#include <iostream>

SmartGuard::SmartGuard()
    : m_speed(100.f),
    m_randomChangeInterval(sf::seconds(3.f))
{
    ResourceManager& resourceManager = ResourceManager::getInstance();


    // Load the sprite sheet
   /* if (!m_texture.loadFromFile("smartGuardSprite.png")) {
        std::cerr << "Failed to load guard sprite sheet" << std::endl;
    }*/

    sf::Sprite& sprite = getSprite();

    // Setup the sprite
    sprite.setTexture(resourceManager.getTexture("smartGuardSprite.png"));
    sprite.setTextureRect(sf::IntRect(0, 0,static_cast<int>(m_frameWidth), static_cast<int>(m_frameHeight)));
    // m_sprite.setScale(1.f, 1.f); // Scale as needed

     // Randomize initial behavior
    randomizeBehavior();
}





void SmartGuard::setPlayerPosition(const sf::Vector2f& playerPos) {
    m_playerPosition = playerPos;
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
    

    sf::Vector2f direction = m_playerPosition - getPosition();
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

    sf::Sprite& sprite = getSprite();

    // Advance the animation frame every 100ms
    if (m_animationClock.getElapsedTime() >= sf::milliseconds(100)) {
        m_animationFrame = (m_animationFrame + 1) % 4;
        m_animationClock.restart();
    }

    // Determine texture row based on movement direction
    int textureX = m_animationFrame * static_cast<int>(m_frameWidth);
    int textureY = 0;

    if (m_velocity.y > 0) {
        textureY = 0;  // Moving down
    }
    else if (m_velocity.y < 0) {
        textureY = static_cast<int>(m_frameHeight * 2);  // Moving up
    }
    else if (m_velocity.x > 0) {
        textureY = static_cast<int>(m_frameHeight);  // Moving right
    }
    else if (m_velocity.x < 0) {
        textureY = static_cast<int>(m_frameHeight);  // Moving left
    }

    sprite.setTextureRect(sf::IntRect(textureX, textureY, static_cast<int>(m_frameWidth), static_cast<int>(m_frameHeight)));
}


void SmartGuard::update(float deltaTime) {

    sf::Sprite& sprite = getSprite();

    m_previousPosition = getPosition();

    calculateVelocity();
    sprite.move(m_velocity * deltaTime);

    updateAnimation();

    if (m_directionChangeClock.getElapsedTime() >= m_randomChangeInterval) {
        randomizeBehavior();
        m_directionChangeClock.restart();
    }
}



void SmartGuard::handleCollisionWith(Wall&) {
  //  std::cout << "SmartGuard hit a wall! Changing direction.\n";

    if (m_velocity.x != 0 || m_velocity.y != 0) {
        // First, switch to alternate direction
        setVelocity(alternateDirection);
    }
    else {
        // If alternate direction is also blocked, try random direction
        moveInAnyAvailableDirection();
    }
}




void SmartGuard::handleCollisionWith(Bomb&, bool ) {
    

    // Revert position
    revertPosition();


    // Adjust velocity to move away from the bomb
    m_velocity = -m_velocity; // Reverse direction
    randomizeBehavior();      // Optionally randomize behavior to avoid getting stuck
}

void SmartGuard::handleCollisionWith(Guard&) {
  //  std::cout << "SmartGuard collided with another Guard.\n";
    m_velocity = sf::Vector2f(0.f, 0.f);
}








sf::CircleShape SmartGuard::getCollisionShape() const {
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
        getPosition().x + m_frameWidth / 2 - (5 * CIRCLRE_OFFSET),
        getPosition().y + m_frameHeight / 2 - (6 * CIRCLRE_OFFSET)
    );

    return collisionEllipse;
}

void SmartGuard::setVelocity(Direction dir) {
    switch (dir) {
    case UP:    m_velocity = { 0.f, -m_speed }; break;
    case DOWN:  m_velocity = { 0.f, m_speed }; break;
    case LEFT:  m_velocity = { -m_speed, 0.f }; break;
    case RIGHT: m_velocity = { m_speed, 0.f }; break;
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
