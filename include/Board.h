#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>
#include "Wall.h"
#include "Door.h"
#include "Robot.h"
#include "SmartGuard.h"
#include "StupidGuard.h"
#include "Rock.h"
#include "Bomb.h"
#include "Coin.h"
#include "ToolbarGame.h"
#include <cstdlib>
#include <ctime>
#include <Present.h>
#include "RemoveGuard.h"
#include "ExtraLife.h"
#include "FreezeGuard.h"
#include "increaseTime.h"

class Board {
public:
    Board();
    void PowerUp(const char choice);
    bool loadFromFile(const std::string& fileName, int level);
    void display(sf::RenderWindow& window);
    void handleMouseClick(sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);
    int update(float deltaTime);
    void startTimer();
    bool isLevelComplete();
    void togglePause();
    void reset();
    bool isPaused();

private:
    bool loadPresent(const std::string& fileName);
    bool isPresentAtPosition(const sf::Vector2f& position);
    void checkIfSmartGuard(MovingGameObject* obj);
    void removeAllBombs();
    bool isGuardSmart();
    void handleCollisions();
    void GenerateBomb();
    void resetObjectsLocation();
    bool m_pause;            
    bool m_pausedByHit;     
    bool m_levelComplete;
    int m_rows, m_cols, m_lives;
    int m_guardCount;
    int m_currentLevel;
    sf::Clock m_pauseClock;  
    float m_pauseDuration;   
    sf::Vector2f m_robotStartingPosition;
    sf::Vector2f m_cellSize;
    std::vector<std::unique_ptr<GameObject>> m_objects;       
    std::vector<std::unique_ptr<MovingGameObject>> m_movingObjects; 
    std::unique_ptr<Robot> m_robot;
    ToolbarGame m_Toolbar;
};
