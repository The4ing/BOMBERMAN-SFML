#include "Robot.h"
#include <iostream>
#include <set>

Robot::Robot()
    : m_direction(STAND),
    m_animationFrame(0),
    m_robotHit(false),
    m_animationTimer(sf::milliseconds(100))
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("robot_spritesheet.png"));
    sf::Sprite& sprite = getSprite();
    sprite.setTexture(resourceManager.getTexture("robot_spritesheet.png"));
    sprite.setTextureRect(sf::IntRect(4 * SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
    setScale(ROBOT_SCALE, ROBOT_SCALE);
}

void Robot::update(float deltaTime) {
    sf::Sprite& spriteRobot = getSprite();
    if (m_robotHit) { // Robot is in death state
        int deadFrame = (m_animationClock.getElapsedTime().asMilliseconds() / 100);
        if (deadFrame < 7) {
            spriteRobot.setTextureRect(sf::IntRect(deadFrame * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT));
        }
        else {
            spriteRobot.setTextureRect(sf::IntRect(6 * SPRITE_WIDTH, 1 * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT)); // Stay on last frame
        }
        m_robotHit = false;
        return; // Skip movement when dead
    }
    m_velocity = { 0.f, 0.f }; // Reset velocity before checking input
    // Prioritize one direction at a time
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_velocity.y = -ROBOT_SPEED;
        m_direction = UP;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_velocity.y = ROBOT_SPEED;
        m_direction = DOWN;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_velocity.x = -ROBOT_SPEED;
        m_direction = LEFT;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_velocity.x = ROBOT_SPEED;
        m_direction = RIGHT;
    }
    // Move based on updated velocity
    m_previousPosition = spriteRobot.getPosition();
    spriteRobot.move(m_velocity * deltaTime);

    // Handle animation updates for movement
    if (m_velocity.x != 0 || m_velocity.y != 0) {
        if (m_animationClock.getElapsedTime() > m_animationTimer) {
            m_animationFrame = (m_animationFrame + 1) % 3;
            int textureX = (m_animationFrame + ((m_direction - 1) * 3)) * SPRITE_WIDTH;
            spriteRobot.setTextureRect(sf::IntRect(textureX, 0, SPRITE_WIDTH, SPRITE_HEIGHT));
            m_animationClock.restart();
        }
    }
}

char Robot::getSymbol() const {
    return '/'; 
}
void Robot::draw(sf::RenderWindow& window) const {
    window.draw(getSprite());
}


void Robot::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); 
}

void Robot::handleCollisionWith(Wall& wall) {
    resolveCollision(wall);
}

void Robot::handleCollisionWith(Rock& rock) {
    resolveCollision(rock);
}

void Robot::handleCollisionWith(Door& door) {
    resolveCollision(door);
}

void Robot::handleCollisionWith(Guard& guard) {
    if (!m_robotHit) {  
        m_robotHit = true;
        m_animationClock.restart(); 
    }
}

void Robot::handleCollisionWith(Bomb&, bool isExploding) {
    if (isExploding) {
        m_robotHit = true;
    }

}

void Robot::resolveCollision(const GameObject& object) {

    sf::FloatRect robotBounds = getBoundingBox();
    sf::FloatRect objectBounds = object.getBoundingBox();

    float overlapLeft = robotBounds.left + robotBounds.width - objectBounds.left;
    float overlapRight = objectBounds.left + objectBounds.width - robotBounds.left;
    float overlapTop = robotBounds.top + robotBounds.height - objectBounds.top;
    float overlapBottom = objectBounds.top + objectBounds.height - robotBounds.top;

    // Check if there's a collision
    if (overlapLeft > 0 && overlapRight > 0 && overlapTop > 0 && overlapBottom > 0) {
        // Restore the robot's previous position
        setPosition(m_previousPosition.x, m_previousPosition.y);

        // Stop the robot's velocity to prevent further movement into the object
        m_velocity = { 0.f, 0.f };
    }
}

sf::CircleShape Robot::getCollisionShape() const {
    sf::CircleShape collisionCircle;
    collisionCircle.setRadius(SPRITE_HEIGHT);
    // Scale it horizontally to form an ellipse
    float horizontalScale = 0.7f;  
    float verticalScale = 1.f;    
    collisionCircle.setScale(horizontalScale, verticalScale);

    collisionCircle.setPosition(getPosition().x + SPRITE_WIDTH / 2 - 10,
        getPosition().y + SPRITE_HEIGHT / 2 - 5);
    return collisionCircle;
}

const bool Robot::isRobotHit() const  {  
    return m_robotHit;
}

void Robot::setHitStatus(bool status) {
    m_robotHit = status;
}
