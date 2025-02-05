#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <sstream>
#include "ResourceManager.h"



class ToolbarGame {

public:

    ToolbarGame();
   

    //mute:
    void toggleMute();
    void handleMouseClick(const sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);

    const int getHeartCount() const ;
    void IncreaseHeart(const bool status);
    void draw(sf::RenderWindow& m_window);

    void addToScore(int addedScore);
    // Timer functions
    void setTimer(const float duration);
   // void callUpdateToolbar(const float deltaTime);
    //void CallUpdateTimer();
    float getTimeLeft() const;           // Get the time left for the level
    float getLevelDuration() const;

    void IncreaseTime(const int extraTime);
    std::string getTimeString() const;
    void startTimer();
    void ShowPresent(const char Present);
    void updateTimerDisplay(const  float deltaTime);
    bool getIsTimerRunning() const;





private:
    //for timer
   
    sf::Text m_presentText;
    sf::Clock m_presentClock;
    sf::Text m_scoreText;
    sf::Sprite m_timer;
    std::vector<sf::Sprite> m_heart;
    sf::Sprite m_muteButton;       // Sprite for the mute button
    

    int m_score;
   

    float m_LevelDuration;        // Total duration of the level
    float m_TimeLeft;             // Time remaining for the level
    sf::Clock m_clock;  // SFML Clock for timing
    bool m_isTimerRunning;  // Timer running status
    sf::RectangleShape m_progressBar;
    int m_num_heart;
    //for mute:
  
    bool m_isMuted;     // Mute state
    void animateProgressBar(const float deltaTime);

    void setLevelDuration(const float duration);
    void UpdateTimer();

};
