#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>  // Include SFML clock
#include <sstream>
#include "Cell.h"
#include "Wall.h"
#include "Empty.h"
#include "Door.h"
#include "Robot.h"
#include "Guard.h"
#include "Rock.h"

// Enum to define power-up choices
enum powerUps {
    FreezeGuards,
    ExtraLife,
    RemovedGuard,
    TimeIncrease
};

enum objects {
	WALL,
	ROCK,
    ROBOT,
	GUARD,
    DOOR,
    EMPTY,
    TEXTURE_COUNT
};

class Board {
public:
    Board();
    void UpdateTimer();
    void PowerUp(const powerUps choice);
    void FreezeAllGuards(const bool status);
    void GrantExtraLife();
    //void RemoveGuard();

    //this is for the timer 
    void IncreaseTime(const int extraTime);
    std::string getTimeString() const;
    void setLevelDuration(float duration);

    // Other members and variables for game state (e.g., guards, lives, timer, etc.)
    void loadFromFile(const std::string& fileName);
    void loadTextures();
    void displayConsole() const;
    void display(sf::RenderWindow& window) const;
    sf::Vector2f getRobotPosition() const;

private:
    bool m_FreezeGuardsStatus;    // Tracks whether the guards are frozen
    int m_lives;                  // Number of lives
    float m_LevelDuration;        // Total duration of the level
    float m_TimeLeft;             // Time remaining for the level
    //std::vector<Guard> guards;  // Vector storing the guards

    //this is for the timer 
    sf::Clock m_clock;  // Starts the clock immediately
    bool m_isTimerRunning;

    std::vector<std::vector<Cell>> m_grid;
    int m_rows, m_cols;

    std::vector<sf::Texture> m_textures;
    sf::Texture wallTexture;
    sf::Texture emptyTexture;
    sf::View m_view;
    sf::Vector2f m_robotPosition;
};
