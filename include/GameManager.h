#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenuDisplay.h"
#include "GameDisplay.h"
#include "SettingsDisplay.h"



class GameManager {
public:
    GameManager();
    void startGame();
    bool loadLevel(const std::string& fileName);

private:
    sf::RenderWindow m_window;   // SFML render window
    MainMenuDisplay m_mainMenu;
    GameDisplay m_gameScreen;
    SettingsDisplay m_settingsScreen;

};
