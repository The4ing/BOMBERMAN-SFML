#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    loadTextures();
    loadFonts();
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

void ResourceManager::loadTextures() {
    std::vector<std::string> textureFiles = {
        "wall.png", "rock.png", "guard.png", "door.png", "empty.png",
        "bomb.png", "present.png", "arrow.png", "bombXPLD.png", "clock.png",
        "explosion.png", "heart.png", "helpBackground.png", "menu.png",
        "mute.png", "Robot.png", "RobotXPL.png", "robot_spritesheet.png",
        "Rock.png", "scary_guard_spritesheet.png", "smartGuardSprite.png",
        "timer.png", "unmute.png"
    };

    for (const auto& filename : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        }
        else {
            m_textures[filename] = std::move(texture);
        }
    }
}

void ResourceManager::loadFonts() {
    std::vector<std::string> fontFiles = {
        "Arial.ttf", "digit.ttf", "PixelFontBlack.otf", "PixelFontWhite.otf"
    };

    for (const auto& filename : fontFiles) {
        sf::Font font;
        if (!font.loadFromFile(filename)) {
            std::cerr << "Error: Could not load font file " << filename << std::endl;
        }
        else {
            m_fonts[filename] = std::move(font);
        }
    }
}

const sf::Texture& ResourceManager::getTexture(const std::string& key) {
    auto it = m_textures.find(key);
    if (it != m_textures.end()) {
        return it->second;
    }
    throw std::runtime_error("Texture not found: " + key);
}

const sf::Font& ResourceManager::getFont(const std::string& key) {
    auto it = m_fonts.find(key);
    if (it != m_fonts.end()) {
        return it->second;
    }
    throw std::runtime_error("Font not found: " + key);
}

void ResourceManager::addSprite(const std::string& key, const sf::Sprite& sprite) {
    m_sprites[key] = sprite;
}

sf::Sprite& ResourceManager::getSprite(const std::string& key) {
    auto it = m_sprites.find(key);
    if (it != m_sprites.end()) {
        return it->second;
    }
    throw std::runtime_error("Sprite not found: " + key);
}

void ResourceManager::removeSprite(const std::string& key)
{
    auto it = m_sprites.find(key);
    if (it != m_sprites.end()) {
        m_sprites.erase(it);  // Correctly removes the sprite from the map
        return;  // Exit the function after successful removal
    }

    std::cerr << "Sprite not found: " + key << std::endl;
}


void ResourceManager::addText(const std::string& key, const sf::Text& text) {
    m_texts[key] = text;
}

sf::Text& ResourceManager::getText(const std::string& key) {
    auto it = m_texts.find(key);
    if (it != m_texts.end()) {
        return it->second;
    }
    throw std::runtime_error("Text not found: " + key);
}
