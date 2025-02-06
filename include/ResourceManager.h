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
const int COIN_SCALE = 15;
const int MAX_ATTEMPTS = 10;
const int NUM_OF_PRESENTS = 4;
const int NUM_XPL = 8;
const int PAUSE_DURATION = 2;
const int COLS = 28;
const int ROWS = 12;
const int NUM_OF_LIVES = 3;
const int COIN_SIZE = 17;
const int CIRCLRE_OFFSET = 10;
const int BOSS_LEVEL = 6;
const int SPRITE_WIDTH = 20;
const int SPRITE_HEIGHT = 30;
const int SPRITE_COLUMNS = 3;
const int SPRITE_ROWS = 4;
const float LEVEL_DURATION = 120.0f;
const float GUARD_WIDTH = 127.5f;
const float GUARD_HEIGHT = 163.33f;
const float TOOLBAR_HEIGHT = 100.0f;
const float WINDOW_WIDTH = 1920.0f;
const float WINDOW_HEIGHT = 1080.0f;
const float SINGLE_SPRITE_DIMENSIONS = 500.0f;
const float CELL_SIZE_X = 68.5714286f, CELL_SIZE_Y = 90.0f;
const float ROBOT_SPEED = 200.f;    
const float ROBOT_SCALE = 2.0f;     
const float GUARD_SPEED = 100.f;
const float GUARD_SCALE = 1.f;
const float GUARD_CHANGE_INTERVAL = 2.f;

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

enum State {
    MAIN_MENU,
    HELP_SCREEN
};

enum Direction {
    INIT, LEFT, DOWN, UP, RIGHT, STAND
};

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
