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
#include "ToolbarGame.h"


// Enum to define power-up choices
enum powerUps {
    FreezeGuards,
    ExtraLife,
    RemovedGuard,
    TimeIncrease
};

class Board {
public:
    Board();

    void PowerUp(const powerUps choice);
    void FreezeAllGuards(const bool status);
    void GrantExtraLife();
    //void RemoveGuard();

   
    int getCols() const;
    int getRows() const;
    bool isWalkable(int row, int col) const;


    //function for uplouding the sound
    //void UploadSound();

    //function for the pictures 
    const sf::Texture& GetTexture(const int choice) const;
    void SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const;
    void callUpdateToolbar(const float deltatime);
    void draw(sf::RenderWindow& window);
    const int getHeartCount();


    // Other members and variables for game state
    void loadFromFile(const std::string& fileName);
    void loadTextures();
    void displayConsole() const;
    void display(sf::RenderWindow& window) const;
    sf::Vector2f getRobotPosition() const;
    sf::Vector2f getRobotScreenPosition(const sf::RenderWindow& window);

    sf::Vector2f getCellSize() const;

private:
    bool m_FreezeGuardsStatus;    // Tracks whether the guards are frozen
    int m_lives;                  // Number of lives


    //void UpdateTimer();
    sf::Vector2f m_cellSize;


    std::vector<std::vector<Cell>> m_grid;
    int m_rows, m_cols;
    ToolbarGame m_Toolbar;
    std::vector<sf::Texture> m_textures;
 

    sf::View m_view;
    sf::Vector2f m_robotPosition;
};
