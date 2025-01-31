#include "ResourceManager.h"


ResourceManager::ResourceManager() {
    loadTexture();
    loadFont();
}

ResourceManager& ResourceManager::getInstance() {
    
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadTexture() {

    std::vector<std::string> m_NamefilesTextures =
    {
        {"wall.png"},
         {"rock.png"},
        { "guard.png"},
        {"door.png"},
        {"empty.png"},
        {"bomb.png"},
        {"present.png"},
        { "arrow.png"},
        {"bombXPLD.png"},
        {"clock.png"},
        {"explosion.png"},
        {"heart.png"},
        {"helpBackground.png"},
        {"menu.png"},
        {"mute.png"},
        {"Robot.png"},
        {"RobotXPL.png"},
        {"robot_spritesheet.png"},
        {"Rock.png"},
        {"scary_guard_spritesheet.png"},
        {"smartGuardSprite.png"},
        {"timer.png"},
        {"unmute.png"},
        {"wall.png"},

    };
    for (const auto& filename : m_NamefilesTextures) {
        if (!m_textures[filename].loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        }
    }
    
}

void ResourceManager::loadFont() {
    std::vector<std::string> fontFiles = {
        "Ariel.ttf",
        "digit.ttf",  // Fixed typo
        "PixelFontBlack.otf",
        "PixelFontWhite.otf"
    };

    for (const auto& filename : fontFiles) {
        sf::Font font;
        if (!font.loadFromFile(filename)) {
            std::cerr << "Error: Could not load font file " << filename << std::endl;
        }
        else {
            m_font[filename] = std::move(font);  // Store the successfully loaded font
        }
    }
}


const sf::Texture& ResourceManager::getTexture(const std::string& key) const {
    return m_textures.at(key);
}

const sf::Font& ResourceManager::getFont(const std::string& key) const {
    return m_font.at(key);
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
