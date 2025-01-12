#pragma once

#include <SFML/Graphics.hpp>
#include "Display.h"

class MainMenuDisplay : public Display {


public:
    MainMenuDisplay(sf::RenderWindow* window, int game);
    void show() override;
    void handleInput() override;
    void Run(); // Main loop for the menu
private:
    sf::Texture m_backgroundTexture; // Texture for the background
    sf::Sprite m_backgroundSprite;  // Sprite to display the background

    sf::RenderWindow* m_window;
    int m_game;

    // Button-related members
    sf::Font m_font;
    sf::Text m_startButton;
    sf::Text m_helpButton;
    sf::Text m_exitButton;

    void handleButtonClick(sf::Vector2i mousePosition);
};
