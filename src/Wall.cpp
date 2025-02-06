#include "Wall.h"
#include <iostream>

Wall::Wall() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("wall.png"));
}

char Wall::getSymbol() const {
    return '#';
}

void Wall::draw(sf::RenderWindow& window) const {
    
    window.draw(getSprite());
}

void Wall::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}



