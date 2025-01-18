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
#include "Guard.h"
#include "Rock.h"

const int NUM_HEART = 3;

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
    HEART,
    CLOCK,
    ARROW,
    TEXTURE_COUNT,
   
};

class Board {
public:
    Board();
   
    void PowerUp(const powerUps choice);
    void FreezeAllGuards(const bool status);
    void GrantExtraLife();
    //void RemoveGuard();

    // Timer functions
    void setTimer(const float duration)  ;
    void animateProgressBar(float deltaTime, sf::RectangleShape& progressBar) const; 
    void updateTimerDisplay(sf::Text& timerText, sf::RectangleShape& progressBar, sf::Sprite& arrow, std::vector<sf::Sprite>& heart,const  float deltaTime) ;
    float getTimeLeft() const;           // Get the time left for the level
    float getLevelDuration() const;
    void CallUpdateTimer();
    void IncreaseTime(const int extraTime);
    std::string getTimeString() const;
    
    
    //function for uplouding the sound
    //void UploadSound();

    //function for the pictures 
    const sf::Texture& GetTexture(const int choice) const ;
    void SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const ;


    // Other members and variables for game state
    void loadFromFile(const std::string& fileName);
    void loadTextures();
    void displayConsole() const;
    void display(sf::RenderWindow& window) const;
    sf::Vector2f getRobotPosition() const;

private:
    bool m_FreezeGuardsStatus;    // Tracks whether the guards are frozen
    int m_lives;                  // Number of lives


    //for timer
    float m_LevelDuration;        // Total duration of the level
    float m_TimeLeft;             // Time remaining for the level
    sf::Clock m_clock;  // SFML Clock for timing
    bool m_isTimerRunning;  // Timer running status
    void setLevelDuration(const float duration);
    void UpdateTimer();
    


    std::vector<std::vector<Cell>> m_grid;
    int m_rows, m_cols;

    std::vector<sf::Texture> m_textures;
    sf::Texture wallTexture;
    sf::Texture emptyTexture;
    sf::View m_view;
    sf::Vector2f m_robotPosition;
};
