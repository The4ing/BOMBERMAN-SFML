#include "Rock.h"
#include <iostream>

Rock::Rock() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    m_sprite.setTexture(resourceManager.getTexture("Rock.png")); // Assign the texture to the sprite
}

char Rock::getSymbol() const {
    return '#'; // Represents the Rock in the game
}

sf::Vector2f Rock::getPosition() const {
    return m_sprite.getPosition(); // Returns the sprite's current position
}

void Rock::setPosition(float x, float y) {
    m_sprite.setPosition(x, y); // Sets the sprite's position
}

void Rock::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = m_sprite;

    //float windowWidth = 1920.0f; // Example window width
    //float windowHeight = 1080.0f; // Example window height
    //float m_cellSizex = windowWidth / static_cast<float>(17);
    //float m_cellSizey = windowHeight / static_cast<float>(9);

    //sprite.setScale(
    //    m_cellSizex / sprite.getTexture()->getSize().x,
    //    m_cellSizey / sprite.getTexture()->getSize().y
    //); // Scale to fit cell size
    window.draw(sprite);
}

void Rock::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); // Delegate collision handling to the other object
}

void Rock::handleCollisionWith(Robot& robot) {
   // std::cout << "Robot collided with Rock: Interaction triggered.\n";
    // Implement Rock-specific interaction with Robot here
}

void Rock::handleCollisionWith(Wall&) {
    // No-op: Rocks don't react to Walls
}

void Rock::handleCollisionWith(Rock&) {
    // No-op: Rocks don't interact with other Rocks
}

void Rock::handleCollisionWith(Door&) {
    // No-op: Rocks don't react to Doors
}

void Rock::handleCollisionWith(Guard&) {
    // No-op: Rocks don't react to Guards
}
void Rock::handleCollisionWith(Present& Present)
{
    //do nothing 
}
void Rock::handleCollisionWith(Bomb&, bool isExploding) {
    // No-op: Rocks don't react to Guards
}
sf::FloatRect Rock::getBoundingBox() const {
    return m_sprite.getGlobalBounds(); // Returns the bounding box of the Rock
}

void Rock::setScale(float scaleX, float scaleY) {
    m_sprite.setScale(scaleX, scaleY);
}
