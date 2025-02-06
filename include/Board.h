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
   


    //const sf::Texture& GetTexture(const int choice) const;
    void SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const;
    //void callUpdateToolbar(float deltatime);
    void draw(sf::RenderWindow& window);
    const int getHeartCount();

    // Other members and variables for game state
    bool loadFromFile(const std::string& fileName, int level);
    bool loadPresent(const std::string& fileName);
    bool isPresentAtPosition(const sf::Vector2f& position);
    void display(sf::RenderWindow& window);

    

    sf::Vector2f getCellSize() const;
    void handleMouseClick(sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);
    bool setSmartGuard();

    int update(float deltaTime);
    void removeAllBombs();
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    bool isGuardSmart();
    void showTransitionScreen(sf::RenderWindow& window, const std::string& message, sf::Color backgroundColor);
    void handleCollisions();
    void setPause();
    void startTimer();
    void GenerateBomb();
    bool isLevelComplete();
    void togglePause();
    void reset();
    bool isPaused();
    void resetObjectsLocation();

private:

    void checkIfSmartGuard(MovingGameObject* obj);
    bool m_FreezeGuardsStatus;    // Tracks whether the guards are frozen
    int m_lives;                  // Number of lives
    int frame_counter;
    bool m_pause;            // Game is paused
    sf::Clock m_pauseClock;  // Timer for pause duration
    float m_pauseDuration;   // Pause duration (2 seconds)
    bool m_pausedByHit;      // Track if pause was triggered by robot hit

    sf::Vector2f m_cellSize;
    std::vector<std::unique_ptr<GameObject>> m_objects;          // Static objects (e.g., walls, rocks)
    std::vector<std::unique_ptr<MovingGameObject>> m_movingObjects; // Moving objects (e.g., robot, guards)
    std::unique_ptr<Robot> m_robot;
    int m_rows, m_cols;
    bool m_levelComplete;
    int m_guardCount;
    int m_currentLevel;
    ToolbarGame m_Toolbar;
    sf::Vector2f m_robotStartingPosition;
    sf::View m_view;
};
