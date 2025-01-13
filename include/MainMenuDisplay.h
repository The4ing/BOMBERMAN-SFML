#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Added for sf::Music
#include "Display.h"
const int START_GAME = 1;
class MainMenuDisplay : public Display {
public:
    MainMenuDisplay(sf::RenderWindow* window, int game);
    void show() override; // Displays the menu or help screen
    int handleInput() override; // Handles user input
    void Run(); // Main loop for the menu

private:
    // State enumeration for the menu
    enum State {
        MAIN_MENU,
        HELP_SCREEN
    };

    State m_state; // Tracks the current state

    sf::RenderWindow* m_window;
    int m_game;

    // Music
    sf::Music menuMmusic;

    // Main menu background
    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    // Help screen background
    sf::Texture m_helpBackgroundTexture;

    // Buttons and text
    sf::Font m_font;
    sf::Text m_startButton;
    sf::Text m_helpButton;
    sf::Text m_exitButton;

    // Help screen text
    sf::Text m_helpText;

     //add
     //sf::RectangleShape m_robotArea;  // Hover area
    //sf::Text m_hoverExplanationText; // Tooltip text


    // Helper methods
    int handleButtonClick(sf::Vector2i mousePosition);
    void configureButton(sf::Text& button, const std::string& label, const sf::Color& color, int yOffset);
};
