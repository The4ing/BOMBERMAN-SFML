#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenuDisplay.h"
#include "GameDisplay.h"
#include "SettingsDisplay.h"
#include "Board.h"
#include "Utilities.h"
#include "Robot.h" // Include Robot class
#include <set> // Include for std::set

class GameManager {
public:
    GameManager();
    void newGame();
    void startGame();
    bool loadLevel(const std::string& fileName);
    void processGameEvents();
    void handleMoveKeys(sf::Keyboard::Key key, const bool isPressed);
    void setRobotPosition();

private:
    sf::RenderWindow m_window;   // SFML render window
    sf::Vector2f m_cellSize;
    MainMenuDisplay m_mainMenu;
    GameDisplay m_gameScreen;
    SettingsDisplay m_settingsScreen;
    Board m_board;
    Robot m_robot;              // Add Robot instance
    int m_robotLives;
    Direction m_robotDirection;
    // Timer for game events
    sf::Font m_font;
    sf::Text m_timerText;
    bool m_pause;
    bool m_arrowKeyPressed;
    std::set<sf::Keyboard::Key> m_activeKeys;

    sf::Texture m_BackgroundGameTexture;
    sf::Sprite m_BackgroundGameSprite;
};
