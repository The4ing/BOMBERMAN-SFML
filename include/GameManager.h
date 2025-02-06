#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <vector>
#include <memory>
#include "MainMenuDisplay.h"
#include "Board.h"
#include "Robot.h"
#include "MovingGameObject.h"

class GameManager {
public:
    GameManager();
    void newGame();
    void startGame();
    void processGameEvents();
    void loadNextLevel();

private:
    sf::Sprite m_muteButtonSprite;
    sf::RenderWindow m_window;
    MainMenuDisplay m_mainMenu;
    Board m_board;
    sf::Sprite m_backgroundSprite;
    int m_currentLevel;
    std::string m_gameMusic;

};
