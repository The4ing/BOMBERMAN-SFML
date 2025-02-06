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
    void toggleMute();
    void handleMouseClick(const sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);
    const int getHeartCount() const ;
    void IncreaseHeart(const bool status);
    void draw(sf::RenderWindow& m_window);
    void setLevel(int level);
    void addToScore(int addedScore);
    void setTimer(const float duration);
    float getTimeLeft() const;           
    float getLevelDuration() const;
    void IncreaseTime(const int extraTime);
    std::string getTimeString() const;
    void startTimer();
    void ShowPresent(const char Present);
    void updateTimerDisplay(const  float deltaTime);
    bool getIsTimerRunning() const;
    void pauseTimer();
    void resumeTimer();
    int getScore();

private:
    void animateProgressBar(const float deltaTime);
    void setLevelDuration(const float duration);
    void UpdateTimer();
    sf::Sprite m_presentText;
    sf::Clock m_presentClock;
    sf::Text m_scoreText;
    sf::Text m_levelText;
    sf::Sprite m_timer;
    std::vector<sf::Sprite> m_heart;
    sf::Sprite m_muteButton;       
    float m_timePaused;
    int m_score;
    float m_LevelDuration;        
    float m_TimeLeft;           
    sf::Clock m_clock;  
    bool m_isTimerRunning;  
    bool m_isPaused;  
    sf::RectangleShape m_progressBar;
    int m_num_heart;
    bool m_isMuted;    
};
