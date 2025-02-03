#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    loadTextures();
    loadFonts();
    loadMusic();
    loadMusic();
    loadSound();
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}


void ResourceManager::loadMusic() {
    std::vector<std::pair<std::string, std::string>> musicFiles = {
        {"menuMusic", "menuMusic.ogg"},
        {"startGame", "gamePlay.ogg"},
        {"bossGame", "bossGame.ogg"},
    };
    for (const auto& [key, filename] : musicFiles) {
        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
        if (!music->openFromFile(filename)) {
            std::cerr << "Error: Could not load music file " << filename << std::endl;
        }
        else {
            m_music[key] = std::move(music);
        }
    }
}




void ResourceManager::loadSound() {
    std::vector<std::pair<std::string, std::string>> soundFiles = {
        {"ButtonMusic", "ButtonMusic.ogg"},
        {"jump", "assets/sounds/jump.wav"},
        {"click", "assets/sounds/click.wav"}
    };
    for (const auto& [key, filename] : soundFiles) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filename)) {
            std::cerr << "Error: Could not load sound file " << filename << std::endl;
            continue;
        }
        m_soundBuffers[key] = std::move(buffer);  // Store buffer
        m_sounds[key].setBuffer(m_soundBuffers[key]);  // Assign buffer to sound
    }
}





void ResourceManager::loadTextures() {
    std::vector<std::string> textureFiles = {
        "wall.png", "rock.png", "guard.png", "door.png", "empty.png",
        "bomb.png", "present.png", "arrow.png", "bombXPLD.png", "clock.png",
        "explosion.png", "heart.png", "helpBackground.png", "menu.png",
        "mute.png", "Robot.png", "RobotXPL.png", "robot_spritesheet.png",
        "Rock.png", "scary_guard_spritesheet.png", "smartGuardSprite.png",
        "timer.png", "unmute.png","lost_life_screen.png"
    };

    for (const auto& filename : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        } else {
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
        } else {
            m_fonts[filename] = std::move(font);
        }
    }
}




sf::Sound& ResourceManager::getSound(const std::string& key) {
    auto it = m_sounds.find(key);
    if (it != m_sounds.end()) {
        return it->second;
    }
    throw std::runtime_error("Sound not found: " + key);
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

sf::Music& ResourceManager::getMusic(const std::string& key) {
    auto it = m_music.find(key);
    if (it != m_music.end()) {
        return *(it->second);  // Dereference unique_ptr
    }
    throw std::runtime_error("Music not found: " + key);
}


sf::Text& ResourceManager::getText(const std::string& key) {
    auto it = m_texts.find(key);
    if (it != m_texts.end()) {
        return it->second;
    }
    throw std::runtime_error("Text not found: " + key);
}


void ResourceManager::addText(const std::string& key, const sf::Text& text) {
    m_texts[key] = text;
}

