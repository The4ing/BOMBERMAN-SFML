//#pragma once
//
//#include "Guard.h"
//#include <SFML/Graphics.hpp>
//#include "Utilities.h"
//
//
//
//class SmartGuard : public Guard {
//public:
//    void setPosition(float newX, float newY) override;
//    void update(float deltaTime) override;
//    void draw(sf::RenderWindow& window) const override;
//    void handleInput(sf::Keyboard::Key key, bool isPressed) override;
//    
//
//
//
//private:
//    sf::Sprite m_sprite;             // Robot's sprite
//    sf::Texture m_texture;           // Texture for the robot's spritesheet
//
//
//    sf::Vector2f m_velocity;
//    bool m_CanMove;
//};