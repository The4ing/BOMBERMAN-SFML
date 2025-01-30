#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <sstream>


const int NUM_HEART = 3;


enum toolbarObjects {

     HEART,
    CLOCK,
    ARROW,
    SIZE_TOOLBAR,
    BAR,
    TIMERTEXT,
};

enum objects {
    WALL,
    ROCK,
    ROBOT,
    GUARD,
    DOOR,
    BOMB,
    EMPTY,
    TEXTURE_COUNT,
   

};
class ToolbarGame {

public:

    ToolbarGame();
    void LoudSprite();
    void loadTextures();
    const sf::Texture& GetTexture(const int& choice) const;

    //mute:
    void toggleMute();
    void handleMouseClick(const sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition);

    const int getHeartCount();
    void draw(sf::RenderWindow& m_window);


    // Timer functions
    void setTimer(const float duration);
    void callUpdateToolbar(const float deltaTime );
    float getTimeLeft() const;           // Get the time left for the level
    float getLevelDuration() const;
    void CallUpdateTimer();
    void IncreaseTime(const int extraTime);
    std::string getTimeString() const;
    void startTimer();


    
  


private:
    //for timer
    sf::Font m_font;
    float m_LevelDuration;        // Total duration of the level
    float m_TimeLeft;             // Time remaining for the level
    sf::Clock m_clock;  // SFML Clock for timing
    bool m_isTimerRunning;  // Timer running status
    sf::Text m_timerText;
    std::vector<sf::Texture> m_ToolbatTexture;
    sf::Sprite m_clockHand;
    sf::Sprite m_arrow;
    std::vector<sf::Sprite> m_heart;
    sf::RectangleShape m_progressBar;

    //for mute:
    sf::Sprite m_muteButton;       // Sprite for the mute button
    sf::Texture m_muteTexture;     // Mute icon texture
    sf::Texture m_unmuteTexture;   // Unmute icon texture
    bool m_isMuted = false;        // Mute state

    void animateProgressBar(const float deltaTime);
    void updateTimerDisplay(const  float deltaTime);
    void SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const;
    void setLevelDuration(const float duration);
    void UpdateTimer();

};
