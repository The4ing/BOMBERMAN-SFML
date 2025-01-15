#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Added for sf::Music
#include "Display.h"
#include <string>
const int START_GAME = 1;

//for explanation in the help menu 
//struct HelpObject {
//    sf::FloatRect bounds;  // Position and size of the object
//    std::string explanation;  // Explanation for the object
//};


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

    // Tooltip text for hover
    sf::Text m_hoverExplanationText;
    sf::Text m_instructionText;

    // Helper methods
    int handleButtonClick(sf::Vector2i mousePosition);
    void handleHover(const sf::Vector2i mousePosition);
    void configureButton(sf::Text& button, const std::string& label, const sf::Color& color, int yOffset);

    sf::SoundBuffer m_buttonClickBuffer;
    sf::Sound m_buttonClickSound;

    // Vector of textures and sprites for help objects
    std::vector<std::pair<sf::Sprite, std::string>> m_helpObjects; // Pair of sprite and explanation

    // Methods to initialize help objects with textures
    void initializeHelpObjects();
    // Class member to store textures
    std::vector<sf::Texture> m_textures;
};
