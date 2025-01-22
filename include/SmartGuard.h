#pragma once
#include "Guard.h" // Assuming Guard is the base class for SmartGuard
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

class SmartGuard : public Guard {
public:
    SmartGuard(); // Constructor declaration

    void setPosition(float newX, float newY) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
    void handleInput(sf::Keyboard::Key key, bool isPressed) override;
  
     sf::Vector2f getPosition() const override;
   

private:
     
};
