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
    //void LoudSprite();
    //void loadTextures();
   // const sf::Texture& GetTexture(const int& choice) const;

    //mute:
    void toggleMute();
    void handleMouseClick(const sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);

    const int getHeartCount() const ;
    void IncreaseHeart(const bool status);
    void draw(sf::RenderWindow& m_window);


    // Timer functions
    void setTimer(const float duration);
    void callUpdateToolbar(const float deltaTime);
    float getTimeLeft() const;           // Get the time left for the level
    float getLevelDuration() const;
    void CallUpdateTimer();
    void IncreaseTime(const int extraTime);
    std::string getTimeString() const;
    void startTimer();







private:
    //for timer
   
   

    //sf::RectangleShape m_timerBackground;
    //sf::Sprite m_clockHand;
    //sf::Sprite m_arrow;
    sf::Sprite m_timer;
    std::vector<sf::Sprite> m_heart;
    sf::Sprite m_muteButton;       // Sprite for the mute button
    


    //std::vector<sf::Texture> m_ToolbatTexture;
    //sf::Font m_font;
    //sf::Text m_timerText;
    
    
    //sf::Texture m_muteTexture;     // Mute icon texture
    //sf::Texture m_unmuteTexture;   // Unmute icon texture
    //void SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const;

    

    float m_LevelDuration;        // Total duration of the level
    float m_TimeLeft;             // Time remaining for the level
    sf::Clock m_clock;  // SFML Clock for timing
    bool m_isTimerRunning;  // Timer running status
    sf::RectangleShape m_progressBar;
    int m_num_heart;
    //for mute:
  
    bool m_isMuted;     // Mute state
    void animateProgressBar(const float deltaTime);
    void updateTimerDisplay(const  float deltaTime);
    void setLevelDuration(const float duration);
    void UpdateTimer();

};
