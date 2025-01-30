#include "Bomb.h"
#include <iostream>

// Constructor
Bomb::Bomb(const sf::Texture& texture)
    : m_startTime(std::chrono::steady_clock::now()), m_exploded(false) {
    m_sprite.setTexture(texture);
}

// Draw function
void Bomb::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = m_sprite;

    float windowWidth = 1920.0f;
    float windowHeight = 1080.0f;
    float m_cellSizex = windowWidth / static_cast<float>(17);
    float m_cellSizey = windowHeight / static_cast<float>(9);

    if (m_exploded) {
        static sf::Texture explodedTexture;
        if (explodedTexture.getSize().x == 0) {
            if (!explodedTexture.loadFromFile("explosion.png")) {
                std::cerr << "Failed to load explosion texture!" << std::endl;
                return;
            }
        }
        sprite.setTexture(explodedTexture);

        float explosionScaleX = m_cellSizex * 2.5f;
        float explosionScaleY = m_cellSizey * 2.5f;
        sprite.setScale(
            explosionScaleX / sprite.getTexture()->getSize().x,
            explosionScaleY / sprite.getTexture()->getSize().y
        );
        sprite.setPosition(m_sprite.getPosition().x - 110, m_sprite.getPosition().y - 90);
        window.draw(sprite);
    }
    else {
        sprite.setScale(
            m_cellSizex / sprite.getTexture()->getSize().x,
            m_cellSizey / sprite.getTexture()->getSize().y
        );
        sprite.setPosition(m_sprite.getPosition().x - 20, m_sprite.getPosition().y - 10);
        window.draw(sprite);
    }

    sf::CircleShape collisionShape = getCollisionShape();
    collisionShape.setFillColor(sf::Color::Transparent);
    collisionShape.setOutlineColor(sf::Color::Red);
    collisionShape.setOutlineThickness(1.f);
    window.draw(collisionShape);
}

// Get bomb position
sf::Vector2f Bomb::getPosition() const {
    return m_sprite.getPosition();
}

// Set bomb position
void Bomb::setPosition(float newX, float newY) {
    m_sprite.setPosition(newX, newY);
}

// Update function
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

// Set explosion state
void Bomb::SetXplode() {
    if (!m_exploded) {
        m_exploded = true;
        m_explosionTime = std::chrono::steady_clock::now();
    }
}

// Check if the bomb has exploded
const bool Bomb::CheckBombExplode() const {
    return m_exploded;
}

// Check if the bomb can be removed
const bool Bomb::CanBeRemoved() const {
    if (!m_exploded || !m_explosionTime.has_value()) {
        return false;
    }

    auto elapsed = std::chrono::steady_clock::now() - m_explosionTime.value();
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 2;
}

// Mark bomb for removal
void Bomb::markForRemoval() {
    m_exploded = false;
    m_explosionTime.reset();
}

// Get explosion area
sf::FloatRect Bomb::getExplosionArea() const {
    if (!m_exploded) {
        return {};
    }

    sf::FloatRect explosionBounds = m_sprite.getGlobalBounds();
    float explosionRadius = explosionBounds.width * 1.5f;

    return sf::FloatRect(
        explosionBounds.left - (explosionRadius / 2),
        explosionBounds.top - (explosionRadius / 2),
        explosionRadius,
        explosionRadius
    );
}

// Collision handling
void Bomb::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this, m_exploded);
}

// Preserve all existing collision handlers
void Bomb::handleCollisionWith(Robot&) {}
void Bomb::handleCollisionWith(Wall&) {}
void Bomb::handleCollisionWith(Rock&) {}
void Bomb::handleCollisionWith(Door&) {}
void Bomb::handleCollisionWith(Guard&) {}
void Bomb::handleCollisionWith(Bomb&, bool isExploding) {}

// Get bomb collision shape
sf::CircleShape Bomb::getCollisionShape() const {
    sf::CircleShape collisionCircle;
    collisionCircle.setRadius(30.f);
    float horizontalScale = 0.9f;
    float verticalScale = 1.2f;
    collisionCircle.setScale(horizontalScale, verticalScale);
    collisionCircle.setPosition(m_sprite.getPosition().x + 20 / 2 - 5,
        m_sprite.getPosition().y + 30 / 2 - 5);
    return collisionCircle;
}

// Get explosion bounds
std::vector<sf::FloatRect> Bomb::getExplosionPlusShapeBounds() const {
    std::vector<sf::FloatRect> explosionBounds;

    if (!m_exploded) {
        return explosionBounds;
    }

    float horizontalLength = 220.f;
    float verticalLength = 240.f;
    float thickness = 50.f;
    sf::Vector2f center = m_sprite.getPosition();

    sf::FloatRect horizontalRect(
        center.x - horizontalLength / 2 + 30,
        center.y - thickness / 2 + 50,
        horizontalLength,
        thickness
    );

    sf::FloatRect verticalRect(
        center.x - thickness / 2 + 30,
        center.y - verticalLength / 2 + 55,
        thickness,
        verticalLength
    );

    explosionBounds.push_back(horizontalRect);
    explosionBounds.push_back(verticalRect);

    return explosionBounds;
}
