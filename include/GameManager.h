#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenuDisplay.h"
#include "GameDisplay.h"
#include "SettingsDisplay.h"
#include "Board.h"

enum Direction {
    INIT
    , UP
    , DOWN
    , RIGHT
    , LEFT
    , STAND
};

class GameManager {
public:
    GameManager();
    void newGame();
    void startGame();
    bool loadLevel(const std::string& fileName);
    void processGameEvents();
    void handleMoveKeys(sf::Keyboard::Key key, const bool isPressed);
    
private:
    sf::RenderWindow m_window;   // SFML render window
    MainMenuDisplay m_mainMenu;
    GameDisplay m_gameScreen;
    SettingsDisplay m_settingsScreen;
    Board m_board;
    int m_robotLives;
    //for timer
    sf::Font m_font;          // Font for displaying text
    sf::Text m_timerText;     // Text object for the timer
    bool m_pause;
    bool m_arrowKeyPressed;
    Direction m_robotDirection;
};
