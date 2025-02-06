#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>

const int NUM_HEART = 3;
const int MAX_TIME = 180;
const int DEAD_GUARD_SCORE = 5;
const int LEVEL_COMPLETE_SCORE = 25;
const int GUARDS_PER_LEVEL_SCORE = 3;
const int COIN_SCORE = 1;
const int NUM_PRESENT = 5;
const int START_GAME = 1;
const int NUM_XPL = 8;


enum toolbarObjects {
    HEART,
    TIMER,
    SIZE_TOOLBAR,
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

enum screenStates {
    PLAYING,
    LOST_LIFE,
    LOST_GAME,
    TIMES_UP,
    WON
};

enum Direction {
    INIT, LEFT, DOWN, UP, RIGHT, STAND
};

const float TOOLBAR_HEIGHT = 100.0f;
const float WINDOW_WIDTH = 1920.0f;
const float WINDOW_HEIGHT = 1080.0f;
const float SINGLE_SPRITE_DIMENSIONS = 500.0f;

class ResourceManager {
public:
    static ResourceManager& getInstance();

    void loadTextures();
    void loadFonts();
    void loadMusic();  // No parameters, loads predefined music files
    void loadSound();
    void loadString();

    const sf::Texture& getTexture(const std::string& key);
    const sf::Font& getFont(const std::string& key);
    sf::Music& getMusic(const std::string& key);
    sf::Sound& getSound(const std::string& key);
    sf::Text& getText(const std::string& key);
    const std::string& getString(const std::string& key);
   


    void addText(const std::string& key, const sf::Text& text);
    

private:
    ResourceManager();
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Text> m_texts;
    std::unordered_map<std::string, sf::Font> m_fonts;
    std::unordered_map<std::string, std::unique_ptr<sf::Music>> m_music;
    std::unordered_map<std::string, sf::SoundBuffer> m_soundBuffers;
    std::unordered_map<std::string, sf::Sound> m_sounds;
    std::unordered_map<std::string, std::string> m_HelpXPL;

};
