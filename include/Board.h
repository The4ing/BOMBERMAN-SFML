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

// Enum to define power-up choices
enum object {
    FreezeGuards,
    ExtraLife,
    RemovedGuard,
    TimeIncrease
};

class Board {
public:
    Board();
    void UpdateTimer();
    void PowerUp(const object choice);
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

private:
    bool m_FreezeGuardsStatus;    // Tracks whether the guards are frozen
    int m_lives;                  // Number of lives
    float m_LevelDuration;        // Total duration of the level
    float m_TimeLeft;             // Time remaining for the level
    //std::vector<Guard> guards;  // Vector storing the guards

    //this is for the timer 
    sf::Clock m_clock;  // Starts the clock immediately
    bool m_isTimerRunning;

    std::vector<std::vector<Cell>> grid;
    int m_rows, m_cols;

    sf::Texture wallTexture;
    sf::Texture emptyTexture;
    sf::View m_view;
};
