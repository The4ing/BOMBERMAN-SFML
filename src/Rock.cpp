#include "Rock.h"
#include <iostream>

Rock::Rock() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
   setTexture(resourceManager.getTexture("Rock.png")); // Assign the texture to the sprite
}

char Rock::getSymbol() const {
    return '#'; // Represents the Rock in the game
}

//sf::Vector2f Rock::getPosition() const {
//    return m_sprite.getPosition(); // Returns the sprite's current position
//}

//void Rock::setPosition(float x, float y) {
//    m_sprite.setPosition(x, y); // Sets the sprite's position
//}
//sf::FloatRect Rock::getBoundingBox() const {
//    return m_sprite.getGlobalBounds(); // Returns the bounding box of the Rock
//}
//void Rock::setScale(float scaleX, float scaleY) {
//    m_sprite.setScale(scaleX, scaleY);
//}
void Rock::draw(sf::RenderWindow& window) const {
   
    window.draw(getSprite());
}

void Rock::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); // Delegate collision handling to the other object
}





