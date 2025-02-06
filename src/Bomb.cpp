#include "Bomb.h"
#include <iostream>

Bomb::Bomb()
    : m_startTime(std::chrono::steady_clock::now()), m_exploded(false) {

    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("bomb.png"));
  
}

void Bomb::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = getSprite();

    if (m_exploded) {
        static sf::Texture explodedTexture;
        if (explodedTexture.getSize().x == 0) {
            if (!explodedTexture.loadFromFile("explosion.png")) {
                std::cerr << "Failed to load explosion texture!" << std::endl;
                return;
            }
        }
        sprite.setTexture(explodedTexture);
        sprite.setScale(
            (CELL_SIZE_X * 2.f) / sprite.getTexture()->getSize().x,
            (CELL_SIZE_Y * 2.f) / sprite.getTexture()->getSize().y
        );
        sprite.setPosition(getPosition().x - 45, getPosition().y - 45);
    }
    else {
        sprite.setScale(
            CELL_SIZE_X / sprite.getTexture()->getSize().x,
            CELL_SIZE_Y / sprite.getTexture()->getSize().y
        );
        sprite.setPosition(getPosition().x - 15, getPosition().y);
    }
    window.draw(sprite);
}

char Bomb::getSymbol() const
{
     return 'B'; 
}

void Bomb::update(const float deltaTime) {
    auto elapsed = std::chrono::steady_clock::now() - m_startTime;
  
    if (!m_exploded && std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 4) {
        SetXplode();

    }

    // Ensure the bomb disappears after the explosion
    if (m_exploded && m_explosionTime.has_value()) {
        auto explosionElapsed = std::chrono::steady_clock::now() - m_explosionTime.value();
        if (std::chrono::duration_cast<std::chrono::seconds>(explosionElapsed).count() >= 2) {
            markForRemoval();
        }
    }
}

void Bomb::SetXplode() {
    if (!m_exploded) {
        ResourceManager& resourceManager = ResourceManager::getInstance();
        sf::Sound& explosionSound = resourceManager.getSound("explosion");
        explosionSound.setVolume(25);
        explosionSound.play();
        m_exploded = true;
        m_explosionTime = std::chrono::steady_clock::now();
    }
}

const bool Bomb::CheckBombExplode() const {
    return m_exploded;
}

const bool Bomb::CanBeRemoved() const {
    if (!m_exploded || !m_explosionTime.has_value()) {
        return false;
    }

    auto elapsed = std::chrono::steady_clock::now() - m_explosionTime.value();
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= EXPLOSION_DURATION;
}

void Bomb::markForRemoval() {
    m_exploded = false;
    m_explosionTime.reset();
}

void Bomb::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this, m_exploded); // Delegate collision handling to the other object
}

sf::CircleShape Bomb::getCollisionShape() const {
    sf::CircleShape collisionCircle;
    collisionCircle.setRadius(30.f);
    float horizontalScale = 0.7f;
    float verticalScale = 1.0f;
    collisionCircle.setScale(horizontalScale, verticalScale);
    collisionCircle.setPosition(getPosition().x + 20 / 2 - 10,
        getPosition().y + 30 / 2 - 5);
    return collisionCircle;
}

std::vector<sf::FloatRect> Bomb::getExplosionPlusShapeBounds() const {
    std::vector<sf::FloatRect> explosionBounds;

    if (!m_exploded) {
        return explosionBounds;
    }

    float horizontalLength = 100.f;
    float verticalLength = 140.f;
    float thickness = 25.f;
    sf::Vector2f center = getPosition();

    sf::FloatRect horizontalRect(
        center.x - horizontalLength / 2 + 20,
        center.y - thickness / 2 + 40,
        horizontalLength,
        thickness
    );

    sf::FloatRect verticalRect(
        center.x - thickness / 2 + 25,
        center.y - verticalLength / 2 + 45,
        thickness,
        verticalLength
    );

    explosionBounds.push_back(horizontalRect);
    explosionBounds.push_back(verticalRect);

    return explosionBounds;
}
