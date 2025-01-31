#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>


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

    bool loadTexture(const std::string& filename);
    bool loadFont(const std::string& filename);

    const sf::Texture& getTexture(const std::string& key) const;
    const sf::Font& getFont() const;

    void addSprite(const std::string& key, const sf::Sprite& sprite);
    sf::Sprite& getSprite(const std::string& key);
    void addText(const std::string& key, sf::Text Text);
    sf::Text& getText(const std::string& key);

private:
    ResourceManager() = default;

    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Sprite> m_sprites;
    std::unordered_map<std::string, sf::Text> m_texts;
    //std::unordered_map<std::string, sf::Font> m_font;
    sf::Font m_font;
   
};
