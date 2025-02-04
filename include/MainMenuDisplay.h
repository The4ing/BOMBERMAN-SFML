#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "ResourceManager.h"




const int START_GAME = 1;
const int NUM_XPL = 8;

class MainMenuDisplay {
public:
    MainMenuDisplay(sf::RenderWindow* window, int game);
    void show();           // Displays the menu or help screen
    int handleInput();     // Handles user input
    void Run();            // Main loop for the menu

private:
    // States for the menu
    enum State {
        MAIN_MENU,
        HELP_SCREEN
    };

    State m_state;                // Tracks the current state

    sf::RenderWindow* m_window;   // Render window
    int m_game;                   // Game reference

    // Backgrounds
   
    sf::Sprite m_mainBackgroundSprite;
    sf::Sprite m_helpBackgroundSprite;

    // Fonts and text
    sf::Text m_instructionText;
    sf::Text m_AboutGame;
    // Button sounds

    
    // Help objects (textures and sprites)
   
    std::vector<sf::Sprite> m_helpSprites;
    std::vector<std::string> m_helpExplanations;

    //for making the music in handlehover 
    std::vector<std::string> m_ButtonsXPL;
    std::vector<bool> played;


    // Helper methods
    void configureButton(const std::string& label, const sf::Color& color, int yOffset);
    void initializeHelpObjects();
    void handleHover(const sf::Vector2i mousePosition);
    int handleButtonClick(const sf::Vector2i mousePosition);
};
