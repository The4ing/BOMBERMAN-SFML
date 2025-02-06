#include "Coin.h"
#include "ResourceManager.h"
#include <iostream>

Coin::Coin() : frameTime(0.1f), elapsedTime(0.0f), frameIndex(0), totalFrames(8) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("Coin.png"));
    frameRect = sf::IntRect(0, 0, COIN_SIZE, COIN_SIZE);
    getSprite().setTextureRect(frameRect);
    getSprite().setScale(55.0f, 55.0f); 
}

char Coin::getSymbol() const {
    return '$';
}

void Coin::draw(sf::RenderWindow& window) const {
    window.draw(getSprite());
}

void Coin::update(float deltaTime) {
    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime) {
        elapsedTime = 0.0f;
        frameIndex = (frameIndex + 1) % totalFrames;  
        frameRect.left = frameIndex * COIN_SIZE;
        getSprite().setTextureRect(frameRect);
    }
}

void Coin::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}

sf::CircleShape Coin::getCollisionShape() const {
    sf::CircleShape collisionCircle;
    collisionCircle.setRadius(static_cast<float>(COIN_SIZE));
    float horizontalScale = 0.7f;  
    float verticalScale = 1.f;    
    collisionCircle.setScale(horizontalScale, verticalScale);

    collisionCircle.setPosition(getPosition().x + 30 / 2 - 10,
        getPosition().y + 17 / 2 - 5);
    return collisionCircle;
}
