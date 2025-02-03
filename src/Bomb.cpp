#include "Bomb.h"
#include <iostream>

// Constructor
Bomb::Bomb()
    : m_startTime(std::chrono::steady_clock::now()), m_exploded(false) {

    ResourceManager& resourceManager = ResourceManager::getInstance();
    setTexture(resourceManager.getTexture("bomb.png"));
  
}





// Draw function
void Bomb::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = getSprite();

    float windowWidth = 1920.0f;
    float windowHeight = 1080.0f;
    float m_cellSizex = windowWidth / static_cast<float>(28);
    float m_cellSizey = windowHeight / static_cast<float>(12);

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
            (m_cellSizex * 2.f) / sprite.getTexture()->getSize().x,
            (m_cellSizey * 2.f) / sprite.getTexture()->getSize().y
        );
        sprite.setPosition(getPosition().x - 45, getPosition().y - 45);
    }
    else {
        sprite.setScale(
            m_cellSizex / sprite.getTexture()->getSize().x,
            m_cellSizey / sprite.getTexture()->getSize().y
        );
        sprite.setPosition(getPosition().x - 15, getPosition().y);
    }

    window.draw(sprite);

    // ?? Draw the explosion area as a red rectangle for debugging
    if (m_exploded) {
        for (const sf::FloatRect& rect : getExplosionPlusShapeBounds()) {
            sf::RectangleShape explosionShape(sf::Vector2f(rect.width, rect.height));
            explosionShape.setPosition(rect.left, rect.top);
            explosionShape.setFillColor(sf::Color(255, 0, 0, 100)); // Semi-transparent red
            explosionShape.setOutlineColor(sf::Color::Red);
            explosionShape.setOutlineThickness(2.f);
            window.draw(explosionShape);
        }
    }

    // Draw collision shape
    sf::CircleShape collisionShape = getCollisionShape();
    collisionShape.setFillColor(sf::Color::Transparent);
    collisionShape.setOutlineColor(sf::Color::Red);
    collisionShape.setOutlineThickness(3.f);
    window.draw(collisionShape);
}






char Bomb::getSymbol() const
{
     return 'B'; 
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
    return std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= EXPLOSION_DURATION;
}


// Mark bomb for removal
void Bomb::markForRemoval() {
    m_exploded = false;
    m_explosionTime.reset();
}

// Get the explosion area
sf::FloatRect Bomb::getExplosionArea() const {
    sf::Sprite sprite = getSprite();

    if (!m_exploded) {
        return {};
    }

    sf::FloatRect explosionBounds = getBoundingBox();
    float explosionRadius = explosionBounds.width * 1.5f; // Adjust explosion size if necessary

    return sf::FloatRect(
        explosionBounds.left - (explosionRadius / 2),
        explosionBounds.top - (explosionRadius / 2),
        explosionRadius,
        explosionRadius
    );
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



// Get explosion bounds
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
