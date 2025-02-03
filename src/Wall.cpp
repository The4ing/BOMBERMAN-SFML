#include "Wall.h"
#include <iostream>

Wall::Wall() {
    ResourceManager& resourceManager = ResourceManager::getInstance();


    setTexture(resourceManager.getTexture("wall.png"));
}


//sf::Vector2f Wall::getPosition() const {
//    return m_sprite.getPosition();
//}


//void Wall::setPosition(float x, float y) {
//    m_sprite.setPosition(x, y);
//}
//sf::FloatRect Wall::getBoundingBox() const {
//    return m_sprite.getGlobalBounds();
//}

//void Wall::setScale(float scaleX, float scaleY) {
//    m_sprite.setScale(scaleX, scaleY);
//}
char Wall::getSymbol() const {
    return '#';
}




void Wall::draw(sf::RenderWindow& window) const {
    
    window.draw(getSprite());
}

void Wall::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}



