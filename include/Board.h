#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>
#include "Cell.h"
#include "Wall.h"
#include "Empty.h"
#include "Door.h"
#include "Robot.h"
#include "SmartGuard.h"
#include "StupidGuard.h"
#include "Rock.h"
#include "Bomb.h"
#include "ToolbarGame.h"
#include <cstdlib>
#include <ctime>
#include <Present.h>
#include "RemoveGuard.h"
#include "ExtraLife.h"
#include "FreezeGuard.h"
#include "increaseTime.h"


// Enum to define power-up choices
//enum powerUps {
//    FreezeGuards,
//    ExtraLife,
//    RemovedGuard,
//    TimeIncrease
//};

class Board {
public:
    Board();

    void PowerUp(const char choice);
    //void FreezeAllGuards(const bool status);
    //void GrantExtraLife();

    /* int getCols() const;
     int getRows() const;*/


    const sf::Texture& GetTexture(const int choice) const;
    void SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const;
    void callUpdateToolbar(float deltatime);
    void draw(sf::RenderWindow& window);
    const int getHeartCount();

    // Other members and variables for game state
    bool loadFromFile(const std::string& fileName);
    //void loadTextures();
    // void displayConsole() const;
    void display(sf::RenderWindow& window);

    // New methods for robot position
    //sf::Vector2i getRobotGridPosition() const;
   //
   // 
   // sf::Vector2f getRobotScreenPosition(const sf::RenderWindow& window) ;

    sf::Vector2f getCellSize() const;
    void handleMouseClick(sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);
    bool setSmartGuard(int level);

    int update(float deltaTime);
    void removeAllBombs();
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    bool isGuardSmart(int level);
    void showTransitionScreen(sf::RenderWindow& window, const std::string& message, sf::Color backgroundColor);
    void handleCollisions();
    void setPause();
    void startTimer();
    void GenerateBomb();
    bool isLevelComplete();
private:

    void checkIfSmartGuard(MovingGameObject* obj);
    bool m_FreezeGuardsStatus;    // Tracks whether the guards are frozen
    int m_lives;                  // Number of lives

    bool m_pause;            // Game is paused
    sf::Clock m_pauseClock;  // Timer for pause duration
    float m_pauseDuration;   // Pause duration (2 seconds)
    bool m_pausedByHit;      // Track if pause was triggered by robot hit

    sf::Vector2f m_cellSize;

    std::vector<std::unique_ptr<GameObject>> m_objects;          // Static objects (e.g., walls, rocks)
    std::vector<std::unique_ptr<MovingGameObject>> m_movingObjects; // Moving objects (e.g., robot, guards)
    std::unique_ptr<Robot> m_robot;
    int m_rows, m_cols;
    //    bool m_pause = false;  // ? New flag to freeze game
    bool m_levelComplete;

    ToolbarGame m_Toolbar;
  //  std::vector<sf::Texture> m_textures;
    //  std::vector<sf::Vector2f> m_guardsStartingPositions;
    sf::Vector2f m_robotStartingPosition;
    void resetObjectsLocation();
    sf::View m_view;
};
