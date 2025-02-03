#include "SmartGuard.h"
#include <cmath>
#include <iostream>

SmartGuard::SmartGuard()
    : m_speed(50.f),
    m_randomChangeInterval(sf::seconds(3.f))
{
    ResourceManager& resourceManager = ResourceManager::getInstance();


    sf::Sprite& sprite = getSprite();

    // Setup the sprite
    sprite.setTexture(resourceManager.getTexture("smartGuardSprite.png"));
    sprite.setTextureRect(sf::IntRect(0, 0,static_cast<int>(getFrameWidth()), static_cast<int>(getFrameHight())));
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
    sf::Vector2f velocity = { getVelocity().x + offsetDist(generator),getVelocity().y + offsetDist(generator) };
    setVelocity(velocity);
   
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
    updateVelocity(preferredDirection);
}

void SmartGuard::updateAnimation() {

    sf::Sprite& sprite = getSprite();

    // Advance the animation frame every 100ms
    if (m_animationClock.getElapsedTime() >= sf::milliseconds(100)) {
        setAnimation((getAnimation() + 1) % 4);
        m_animationClock.restart();
    }

    // Determine texture row based on movement direction
    int textureX = getAnimation() * static_cast<int>(getFrameWidth());
    int textureY = 0;

    if (getVelocity().y > 0) {
        textureY = 0;  // Moving down
    }
    else if (getVelocity().y < 0) {
        textureY = static_cast<int>(getFrameHight() * 2);  // Moving up
    }
    else if (getVelocity().x > 0) {
        textureY = static_cast<int>(getFrameHight());  // Moving right
    }
    else if (getVelocity().x < 0) {
        textureY = static_cast<int>(getFrameHight());  // Moving left
    }

    sprite.setTextureRect(sf::IntRect(textureX, textureY, static_cast<int>(getFrameWidth()), static_cast<int>(getFrameHight())));
}


void SmartGuard::update(float deltaTime) {

    sf::Sprite& sprite = getSprite();

    setPrevPpos(getPosition());

    calculateVelocity();
    sprite.move(getVelocity() * deltaTime);

    updateAnimation();

    if (m_directionChangeClock.getElapsedTime() >= m_randomChangeInterval) {
        randomizeBehavior();
        m_directionChangeClock.restart();
    }
}



void SmartGuard::handleCollisionWith(Wall&) {
   std::cout << "SmartGuard hit a wall! Changing direction.\n";

    if (getVelocity().x != 0 || getVelocity().y != 0) {
        // First, switch to alternate direction
        updateVelocity(alternateDirection);
    }
    else {
        // If alternate direction is also blocked, try random direction
        moveInAnyAvailableDirection();
    }
}




void SmartGuard::handleCollisionWith(Bomb&, bool ) {
    

    // Revert position
    getRevert();


    // Adjust velocity to move away from the bomb
    setVelocity(-getVelocity()); // Reverse direction
    randomizeBehavior();      // Optionally randomize behavior to avoid getting stuck
}

void SmartGuard::handleCollisionWith(Guard&) {
  //  std::cout << "SmartGuard collided with another Guard.\n";
    setVelocity(sf::Vector2f(0.f, 0.f));
}








sf::CircleShape SmartGuard::getCollisionShape() const {
    sf::CircleShape collisionEllipse;

    float radiusX = getFrameWidth() / 4;  // Horizontal radius (adjust as needed)
    float radiusY = getFrameHight() / 6; // Vertical radius (adjust as needed)
    collisionEllipse.setRadius(radiusX);  // Base radius (use the larger dimension)

    // Scale it horizontally to form an ellipse
    float horizontalScale = 0.7f;  // Adjust this value for width
    float verticalScale = 1.f;    // Keep this 1.0 to maintain original height
    collisionEllipse.setScale(horizontalScale, verticalScale);
    //  collisionEllipse.setOrigin(radiusX, radiusX);  // Origin remains at center
    collisionEllipse.setPosition(
        getPosition().x + getFrameWidth() / 2 - (5 * CIRCLRE_OFFSET),
        getPosition().y + getFrameHight() / 2 - (6 * CIRCLRE_OFFSET)
    );

    return collisionEllipse;
}

void SmartGuard::updateVelocity(Direction dir) {
    
    switch (dir) {
    case UP:    setVelocity({ 0.f, -m_speed }); break;
    case DOWN:  setVelocity({ 0.f, m_speed }); break;
    case LEFT: setVelocity({ -m_speed, 0.f }); break;
    case RIGHT: setVelocity({ m_speed, 0.f }); break;
    }
}


void SmartGuard::moveInAnyAvailableDirection() {
    std::vector<Direction> possibleDirections = { UP, DOWN, LEFT, RIGHT };
    std::shuffle(possibleDirections.begin(), possibleDirections.end(), std::mt19937(std::random_device()()));

    for (Direction dir : possibleDirections) {
        updateVelocity(dir);
        break;
    }
}
