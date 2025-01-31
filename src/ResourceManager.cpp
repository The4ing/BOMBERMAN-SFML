#include "ResourceManager.h"

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}


bool ResourceManager::loadTexture(const std::string& filename) {
    return m_textures[filename].loadFromFile(filename );
}

bool ResourceManager::loadFont(const std::string& filename) {
    return m_font.loadFromFile(filename);
}

const sf::Texture& ResourceManager::getTexture(const std::string& key) const {
    return m_textures.at(key);
}

const sf::Font& ResourceManager::getFont() const {
    return m_font;
}

void ResourceManager::addSprite(const std::string& key, const sf::Sprite& sprite) {
    m_sprites[key] = sprite;
}

sf::Sprite& ResourceManager::getSprite(const std::string& key) {
    return m_sprites.at(key);
}


void ResourceManager::addText(const std::string& key, sf::Text Text) {
    m_texts[key] = Text;  // Store it in the map with the given key
}

sf::Text& ResourceManager::getText(const std::string& key) {
    return m_texts.at(key);
}
