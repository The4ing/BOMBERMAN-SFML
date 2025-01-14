#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenuDisplay.h"
#include "GameDisplay.h"
#include "SettingsDisplay.h"
#include "Board.h"



class GameManager {
public:
    GameManager();
    void newGame();
    void startGame();
    bool loadLevel(const std::string& fileName);

private:
    sf::RenderWindow m_window;   // SFML render window
    MainMenuDisplay m_mainMenu;
    GameDisplay m_gameScreen;
    SettingsDisplay m_settingsScreen;
    Board m_board;

    //for timer
    sf::Font m_font;          // Font for displaying text
    sf::Text m_timerText;     // Text object for the timer

};
