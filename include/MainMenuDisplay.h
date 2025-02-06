#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "ResourceManager.h"

class MainMenuDisplay {
public:
    MainMenuDisplay(sf::RenderWindow* window, int game);
    void show();          
    int handleInput();     
    void Run();            

private:
    State m_state;              
    sf::RenderWindow* m_window;  
    int m_game;      
    sf::Sprite m_mainBackgroundSprite;
    sf::Sprite m_helpBackgroundSprite;
    sf::Sprite m_esc;
    sf::Text m_instructionText;
    sf::Text m_AboutGame;
    std::vector<sf::RectangleShape> m_rectangles;
    sf::RectangleShape m_textBackground;
    std::vector<sf::Sprite> m_helpSprites;
    std::vector<std::string> m_helpExplanations;
    std::vector<std::string> m_ButtonsXPL;
    std::vector<bool> played;
    void configureButton(const std::string& label, const sf::Color& color, int yOffset);
    void initializeHelpObjects();
    void handleHover(const sf::Vector2i mousePosition);
    int handleButtonClick(const sf::Vector2i mousePosition);
    std::map<std::string, sf::Sprite> m_buttonFrames; 
};
