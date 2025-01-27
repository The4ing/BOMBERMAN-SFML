#include "Bomb.h"
#include <iostream>

// Constructor
Bomb::Bomb(const sf::Texture& texture)
    : m_startTime(std::chrono::steady_clock::now()), m_exploded(false) {
    m_sprite.setTexture(texture);
}

void Bomb::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = m_sprite;

    float windowWidth = 1920.0f;  // Example window width
    float windowHeight = 1080.0f; // Example window height
    float m_cellSizex = windowWidth / static_cast<float>(17);
    float m_cellSizey = windowHeight / static_cast<float>(9);

    if (m_exploded) {
        static sf::Texture explodedTexture;
        if (explodedTexture.getSize().x == 0) { // Load explosion texture only once
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

        // Draw explosion plus shape bounds for debugging
        std::vector<sf::FloatRect> explosionBounds = getExplosionPlusShapeBounds();
        for (const auto& rect : explosionBounds) {
            sf::RectangleShape shape(sf::Vector2f(rect.width, rect.height));
            shape.setPosition(rect.left, rect.top);
            shape.setFillColor(sf::Color::Transparent);
            shape.setOutlineColor(sf::Color::Green);
            shape.setOutlineThickness(1.f);
            window.draw(shape);
        }
    }
    else {
        // Normal bomb rendering
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

void Bomb::handleCollision(GameObject& other) {
    other.handleCollisionWith(*this, m_exploded); // Delegate collision handling to the other object
}


void Bomb::handleCollisionWith(Robot&) {
    std::cout << "Robot collided with Rock: Interaction triggered.\n";
    // Implement Rock-specific interaction with Robot here
}

void Bomb::handleCollisionWith(Wall&) {
    // No-op: Rocks don't react to Walls
}

void Bomb::handleCollisionWith(Rock&) {
    // No-op: Rocks don't interact with other Rocks
}

void Bomb::handleCollisionWith(Door&) {
    // No-op: Rocks don't react to Doors
}

void Bomb::handleCollisionWith(Guard&) {
    // No-op: Rocks don't react to Guards
}
void Bomb::handleCollisionWith(Bomb&, bool isExploding) {
    // No-op: Rocks don't react to Guards
}

sf::CircleShape Bomb::getCollisionShape() const {
    sf::CircleShape collisionCircle;
    collisionCircle.setRadius(30.f);
    // Scale it horizontally to form an ellipse
    float horizontalScale = 0.9f;  // Adjust this value for width
    float verticalScale = 1.2f;    // Keep this 1.0 to maintain original height
    collisionCircle.setScale(horizontalScale, verticalScale);


    collisionCircle.setPosition(m_sprite.getPosition().x + 20 / 2 - 5,
        m_sprite.getPosition().y + 30 / 2 - 5);

    return collisionCircle;
}

std::vector<sf::FloatRect> Bomb::getExplosionPlusShapeBounds() const {
    std::vector<sf::FloatRect> explosionBounds;

    if (!m_exploded) {
        return explosionBounds; // Return empty vector if not exploded
    }

    // Example explosion size values; adjust as needed
    float horizontalLength = 220.f; // Length of horizontal part of the "+"
    float verticalLength = 240.f;   // Length of vertical part of the "+"
    float thickness = 50.f;         // Width of each rectangle (arm thickness)

    // Position of the bomb (center of the "+")
    sf::Vector2f center = m_sprite.getPosition();

    // Horizontal rectangle (centered at the bomb)
    sf::FloatRect horizontalRect(
        center.x - horizontalLength / 2 + 30,  // Left
        center.y - thickness / 2 + 50,        // Top
        horizontalLength,                // Width
        thickness                        // Height
    );

    // Vertical rectangle (centered at the bomb)
    sf::FloatRect verticalRect(
        center.x - thickness / 2 + 30,        // Left
        center.y - verticalLength / 2 + 55,  // Top
        thickness,                       // Width
        verticalLength                   // Height
    );

    explosionBounds.push_back(horizontalRect);
    explosionBounds.push_back(verticalRect);

    return explosionBounds;
}
