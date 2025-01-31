#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "ResourceManager.h"




const int START_GAME = 1;

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
   // sf::Texture m_mainBackgroundTexture;
    sf::Sprite m_mainBackgroundSprite;
    //sf::Texture m_helpBackgroundTexture;
    sf::Sprite m_helpBackgroundSprite;

    // Fonts and text
   // sf::Font m_font;
    sf::Text m_startButton;
    sf::Text m_helpButton;
    sf::Text m_exitButton;
    sf::Text m_hoverExplanationText;
    sf::Text m_instructionText;

    // Button sounds
    sf::SoundBuffer m_buttonClickBuffer;
    sf::Sound m_buttonClickSound;

    // Help objects (textures and sprites)
    std::vector<sf::Texture> m_helpTextures;
    std::vector<sf::Sprite> m_helpSprites;
    std::vector<std::string> m_helpExplanations;


    //for making the music in handlehover 
    std::vector<sf::SoundBuffer> m_ButtonXPL;
    sf::Sound ButtonSounds; // Declare outside the loop, so it persists
    bool played = false;

    // Menu music
    sf::Music m_menuMusic;

    // Helper methods
    void configureButton(sf::Text& button, const std::string& label, const sf::Color& color, int yOffset);
    void initializeHelpObjects();
    void handleHover(const sf::Vector2i mousePosition);
    int handleButtonClick(const sf::Vector2i mousePosition);
};
