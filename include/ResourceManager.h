#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <vector>


const int NUM_HEART = 3;
const int MAX_TIME = 100;

enum toolbarObjects {

    HEART,
    TIMER,
    SIZE_TOOLBAR,
    /*CLOCK,
    ARROW,*/
    // BAR,
    // TIMERTEXT,
};

enum objects {
    WALL,
    ROCK,
    ROBOT,
    GUARD,
    DOOR,
    EMPTY,
    BOMB,
    PRESENT,
    TEXTURE_COUNT,


};
const float TOOLBAR_HEIGHT = 100.0f; // Fixed toolbar height in pixels
const float WINDOW_WIDTH = 1920.0f; // Example window width
const float WINDOW_HEIGHT = 1080.0f; // Example window height
const float SINGLE_SPRITE_DIMENSIONS = 500.0f;


enum Direction {
    INIT
    , LEFT
    , DOWN
    , UP
    , RIGHT
    , STAND
};


class ResourceManager {
public:
    static ResourceManager& getInstance();

    
    void loadTexture();
    void loadFont();

    const sf::Texture& getTexture(const std::string& key) const;
    const sf::Font& getFont(const std::string& key) const;

    void addSprite(const std::string& key, const sf::Sprite& sprite);
    sf::Sprite& getSprite(const std::string& key);
    void addText(const std::string& key, sf::Text Text);
    sf::Text& getText(const std::string& key);

private:
    ResourceManager() ;


    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Sprite> m_sprites;
    std::unordered_map<std::string, sf::Text> m_texts;
    std::unordered_map<std::string, sf::Font> m_font;
  
   
};
