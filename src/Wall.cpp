#include "Wall.h"
#include <iostream>

Wall::Wall() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    m_sprite.setTexture(resourceManager.getTexture("wall.png"));
}

char Wall::getSymbol() const {
    return '#';
}

sf::Vector2f Wall::getPosition() const {
    return m_sprite.getPosition();
}

void Wall::setPosition(float x, float y) {
    m_sprite.setPosition(x, y);
}

void Wall::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = m_sprite;
    window.draw(sprite);
}

void Wall::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}

void Wall::handleCollisionWith(Robot& robot) {
    // std::cout << "Wall collided with Robot\n";
     // No additional behavior, but logic can be extended if needed.
}

void Wall::handleCollisionWith(Wall& wall) {
    // std::cout << "Wall collided with another Wall\n";
     // Walls generally don't react to other walls.
}

void Wall::handleCollisionWith(Rock& rock) {
    //std::cout << "Wall collided with Rock\n";
    // No behavior defined for Wall-Rock collision.
}

void Wall::handleCollisionWith(Door& door) {
    //std::cout << "Wall collided with Door\n";
    // No behavior defined for Wall-Door collision.
}

void Wall::handleCollisionWith(Guard& guard) {
    //std::cout << "Wall collided with Guard\n";
    // No behavior defined for Wall-Guard collision.
}
void Wall::handleCollisionWith(Present& Present)
{
    //do nothing 
}
void Wall::handleCollisionWith(Bomb&, bool isExploding) {
    // No-op: Rocks don't react to Guards
}
sf::FloatRect Wall::getBoundingBox() const {
    return m_sprite.getGlobalBounds();
}

void Wall::setScale(float scaleX, float scaleY) {
    m_sprite.setScale(scaleX, scaleY);
}
