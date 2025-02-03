#include "Door.h"
#include <iostream>

Door::Door() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("door.png")); // Assign the texture to the sprite
}

char Door::getSymbol() const {
    return 'D'; // Represents the Door in the game
}

//sf::Vector2f Door::getPosition() const {
//    return m_sprite.getPosition(); // Returns the sprite's current position
//}

//void Door::setPosition(float x, float y) {
//    m_sprite.setPosition(x, y); // Sets the sprite's position
//}
//void Door::setScale(float scaleX, float scaleY) {
//    m_sprite.setScale(scaleX, scaleY);
//}


void Door::draw(sf::RenderWindow& window) const {
  
    window.draw(getSprite());
}

void Door::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); // Delegate collision handling to the other object
}


//sf::FloatRect Door::getBoundingBox() const {
//
//    return m_sprite.getGlobalBounds(); // Returns the bounding box of the door
//}

