#pragma once
#include "Display.h"

// Derived Class: GameDisplay
class GameDisplay : public Display {
public:
    GameDisplay(sf::RenderWindow* window);
    void show() override;          // Render the game screen
    void handleInput() override;   // Handle input in the game
private:
    sf::RenderWindow* m_window;
};


