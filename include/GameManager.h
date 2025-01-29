#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <vector>
#include <memory>
#include "MainMenuDisplay.h"
#include "GameDisplay.h"
#include "SettingsDisplay.h"
#include "Board.h"
#include "Utilities.h"
#include "Robot.h"
#include "MovingGameObject.h"

class GameManager {
public:
    GameManager();
    void newGame();
    void startGame();
  //  bool loadLevel(const std::string& fileName);
    void processGameEvents();
    void pauseGame(float pauseDuration);
   // void handleMoveKeys(sf::Keyboard::Key key, const bool isPressed);
   // void setRobotPosition();
    char getSingleKeyPress();
    void loadNextLevel();

private:
    sf::RenderWindow m_window;   // SFML render window
    sf::Vector2f m_cellSize;
    MainMenuDisplay m_mainMenu;
    GameDisplay m_gameScreen;
    SettingsDisplay m_settingsScreen;
    Board m_board;

    std::vector<std::unique_ptr<MovingGameObject>> m_movingObjects; // Manage all game objects dynamically

    int m_robotLives;
    Direction m_robotDirection;
    sf::Font m_font;
    sf::Text m_timerText;
    bool m_pause;
    bool m_arrowKeyPressed;
    std::set<sf::Keyboard::Key> m_activeKeys;
    int m_currentLevel; // Tracks the current level 
    sf::Texture m_BackgroundGameTexture;
    sf::Sprite m_BackgroundGameSprite;
};
