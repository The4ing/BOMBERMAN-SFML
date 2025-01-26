#pragma once
#include "MovingGameObject.h"
#include <SFML/Graphics.hpp>
#include "Utilities.h" 
#include <chrono>
#include <optional> // To handle the optional explosion time

static constexpr float EXPLOSION_DURATION = 2.0f; // Duration to show the explosion (in seconds)

class Bomb : public MovingGameObject {
public:
    Bomb(const sf::Texture& texture);

    char getSymbol() const override { return 'B'; }
    void setPosition(float newX, float newY) override;
    void update(const float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::Vector2f getPosition() const override;

    void collideWith(GameObject* other) override;
    void collideWith(Rock* rock) override;
    void collideWith(Wall* wall) override;
    void collideWith(Robot* robot) override;
    void collideWith(Door* door) override;
    void collideWith(Guard* guard) override;
    void collideWith(Bomb* bomb) override;

    sf::FloatRect getExplosionArea() const;
    const bool CheckBombExplode() const;
    const bool CanBeRemoved() const; // Check if the bomb should be removed from the game

private:
    void SetXplode();
    bool m_exploded;
    std::chrono::steady_clock::time_point m_startTime;
    std::optional<std::chrono::steady_clock::time_point> m_explosionTime; // Explosion start time
    
};
