#pragma once
#include "Guard.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <random>

class SmartGuard : public Guard {
public:
    SmartGuard();

    char getSymbol() const override { return '!'; }
    void setPosition(float newX, float newY) override;
    void update(const float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    sf::Vector2f getPosition() const override;

    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void setPlayerPosition(const sf::Vector2f& playerPos);
    


    ///collision

    
   
    

private:
    sf::Vector2f m_playerPosition;
    sf::Vector2f m_velocity;
    sf::Clock m_directionChangeClock;
    sf::Time m_randomChangeInterval;
    sf::Clock m_animationClock;

    float m_speed;
    int m_animationFrame;
    float m_frameWidth;
    float m_frameHeight;

    sf::Texture m_texture;
    sf::Sprite m_sprite;

    void calculateVelocity();
    void randomizeBehavior();
    void updateAnimation();
};
