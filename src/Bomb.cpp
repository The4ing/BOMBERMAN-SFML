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

    float windowWidth = 1920.0f;  // Example window width
    float windowHeight = 1080.0f; // Example window height
    float m_cellSizex = windowWidth / static_cast<float>(17);
    float m_cellSizey = windowHeight / static_cast<float>(9);

    if (m_exploded) {
        static sf::Texture explodedTexture;
        if (explodedTexture.getSize().x == 0) { // Load explosion texture only once
            if (!explodedTexture.loadFromFile("bombXPLD.png")) {
                std::cerr << "Failed to load explosion texture!" << std::endl;
                return;
            }
        }
        sprite.setTexture(explodedTexture); // Use explosion texture
    }

    // Scale the sprite to fit the cell size
    sprite.setScale(
        m_cellSizex / sprite.getTexture()->getSize().x,
        m_cellSizey / sprite.getTexture()->getSize().y
    );

    // Draw the sprite
    window.draw(sprite);
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
}

// Set explosion state
void Bomb::SetXplode() {
    if (!m_exploded) {
        m_exploded = true;
        m_explosionTime = std::chrono::steady_clock::now(); // Start the explosion timer
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
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= EXPLOSION_DURATION;
}

// Get the explosion area
sf::FloatRect Bomb::getExplosionArea() const {
    if (!m_exploded) {
        return {};
    }

    sf::FloatRect explosionBounds = m_sprite.getGlobalBounds();
    float explosionRadius = explosionBounds.width * 1.5f; // Adjust explosion size if necessary

    return sf::FloatRect(
        explosionBounds.left - (explosionRadius / 2),
        explosionBounds.top - (explosionRadius / 2),
        explosionRadius,
        explosionRadius
    );
}

// Collision methods
void Bomb::collideWith(GameObject* other) {
    other->collideWith(this);  // Double dispatch
}

void Bomb::collideWith(Rock* rock) {
    std::cout << "Bomb collided with a Rock!" << std::endl;
}

void Bomb::collideWith(Wall* wall) {
    std::cout << "Bomb collided with a Wall!" << std::endl;
}

void Bomb::collideWith(Robot* robot) {
    std::cout << "Bomb collided with a Robot!" << std::endl;
}

void Bomb::collideWith(Door* door) {
    std::cout << "Bomb collided with a Door!" << std::endl;
}

void Bomb::collideWith(Guard* guard) {
    std::cout << "Bomb collided with a Guard!" << std::endl;
}

void Bomb::collideWith(Bomb* bomb)
{
    std::cout << "Bomb collided with a bomb!" << std::endl;
}
