#include "Coin.h"
#include "ResourceManager.h"
#include <iostream>

Coin::Coin() : frameTime(0.1f), elapsedTime(0.0f), frameIndex(0), totalFrames(8) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("Coin.png"));
    // Assume each frame is 64x64 pixels (adjust based on your sprite sheet)
    frameRect = sf::IntRect(0, 0, 17, 17);
    getSprite().setTextureRect(frameRect);

    // Scale the sprite to make it bigger
    getSprite().setScale(55.0f, 55.0f);  // Double the size of the coin (change values as needed)
}


char Coin::getSymbol() const {
    return '$';
}

void Coin::draw(sf::RenderWindow& window) const {
    window.draw(getSprite());
    sf::CircleShape collisionShape = getCollisionShape();
    collisionShape.setFillColor(sf::Color::Transparent);
    collisionShape.setOutlineColor(sf::Color::Red);
    collisionShape.setOutlineThickness(1.f);
    window.draw(collisionShape);
}

void Coin::update(float deltaTime) {
    elapsedTime += deltaTime;

    // Change frame if enough time has passed
    if (elapsedTime >= frameTime) {
        elapsedTime = 0.0f;
        frameIndex = (frameIndex + 1) % totalFrames;  // Cycle through frames

        // Update texture rect to show next frame
        frameRect.left = frameIndex * 17;  // Move to next frame in the sprite sheet
        getSprite().setTextureRect(frameRect);
    }
}

void Coin::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this);
}

sf::CircleShape Coin::getCollisionShape() const {
    sf::CircleShape collisionCircle;
    collisionCircle.setRadius(17.0f);
    // Scale it horizontally to form an ellipse
    float horizontalScale = 0.7f;  // Adjust this value for width
    float verticalScale = 1.f;    // Keep this 1.0 to maintain original height
    collisionCircle.setScale(horizontalScale, verticalScale);

    collisionCircle.setPosition(getPosition().x + 30 / 2 - 10,
        getPosition().y + 17 / 2 - 5);
    return collisionCircle;
}
