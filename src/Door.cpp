#include "Door.h"
#include <iostream>

Door::Door() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("door.png"));
}

char Door::getSymbol() const {
    return 'D'; 
}
void Door::draw(sf::RenderWindow& window) const {
  
    window.draw(getSprite());
}

void Door::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this); 
}
