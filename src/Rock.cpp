#include "Rock.h"
#include <iostream>

Rock::Rock() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
   setTexture(resourceManager.getTexture("Rock.png")); 
}

char Rock::getSymbol() const {
    return '#'; 
}

void Rock::draw(sf::RenderWindow& window) const {
   
    window.draw(getSprite());
}

void Rock::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); 
}
