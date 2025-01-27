#include "Door.h"
#include <iostream>

Door::Door(const sf::Texture& texture) {
    m_sprite.setTexture(texture); // Assign the texture to the sprite
}

char Door::getSymbol() const {
    return 'D'; // Represents the Door in the game
}

sf::Vector2f Door::getPosition() const {
    return m_sprite.getPosition(); // Returns the sprite's current position
}

void Door::setPosition(float x, float y) {
    m_sprite.setPosition(x, y); // Sets the sprite's position
}

void Door::draw(sf::RenderWindow& window) const {
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

void Door::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); // Delegate collision handling to the other object
}

void Door::handleCollisionWith(Robot& robot) {
    std::cout << "Robot collided with Door: Door interaction triggered.\n";
    // Implement door-specific interaction with Robot here
}

void Door::handleCollisionWith(Wall&) {
    // No-op: Doors don't react to Walls
}

void Door::handleCollisionWith(Rock&) {
    // No-op: Doors don't react to Rocks
}

void Door::handleCollisionWith(Door&) {
    // No-op: Doors don't interact with other Doors
}

void Door::handleCollisionWith(Guard&) {
    // No-op: Doors don't react to Guards
}
void Door::handleCollisionWith(Bomb&, bool isExploding) {
    // No-op: Rocks don't react to Guards
}
sf::FloatRect Door::getBoundingBox() const {
    return m_sprite.getGlobalBounds(); // Returns the bounding box of the door
}

void Door::setScale(float scaleX, float scaleY) {
    m_sprite.setScale(scaleX, scaleY);
}
