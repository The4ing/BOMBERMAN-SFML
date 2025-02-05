#include "ResourceManager.h"

ResourceManager::ResourceManager() {
    loadTextures();
    loadFonts();
    loadMusic();
    loadSound();
    loadString();
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
        {"WallXPL", "WallXPL.ogg"},
        {"RobotXPL", "RobotXPL.ogg"},
        {"BombXPL", "BombXPL.ogg"},
        {"SmartGuardXPL", "SmartGuardXPL.ogg"},
        {"DoorXPL", "DoorXPL.ogg"},
        {"RockXPL", "RockXPL.ogg"},
        {"StupidGuardXPL", "StupidGuardXPL.ogg"},  
        {"PresentXPL", "PresentXPL.ogg"},
        {"coin", "coin.ogg"},
    };

    for (const auto& [key, filename] : soundFiles) {
        // Load directly into the map to ensure persistence
        if (!m_soundBuffers[key].loadFromFile(filename)) {
            std::cerr << "Error: Could not load sound file " << filename << std::endl;
            continue;
        }
        m_sounds[key].setBuffer(m_soundBuffers[key]);
    }
}

void ResourceManager::loadString()
{
    m_HelpXPL = {
        {"WallXPL",  "Wall: An obstacle that blocks the player's path.\n"
        "Walls cannot be passed through,\n"
        "and the player will need to find a way around or use other game mechanics to overcome them."},

        {"RobotXPL",  "Robot:  The main character of the game.\n"
        "This is the entity controlled by the player,\n"
        "who must navigate through different levels and avoid various obstacles to escape to the next area.\n"
        "The robot may have special abilities or movement patterns that make it unique."},

        {"BombXPL",   "Bomb: A dangerous item that can cause harm to the player or enemies when triggered.\n"
        "The player must handle bombs carefully,\n"
        "either by avoiding them or using tools to disarm them before they explode.\n"
        "These can add an element of risk and challenge to the game."},

        {"SmartGuardXPL", "Smart_Guard: An enemy or obstacle that is highly intelligent and can anticipate the player's movements.\n"
        "These guards are programmed with advanced algorithms to track the player's actions,\n"
        "making them difficult to evade. The player must think strategically to avoid being caught."},

        {"DoorXPL", "Door: A gateway that leads the player to the next area or level in the game.\n"
        "Often locked or requiring specific conditions to open,\n"
        "such as finding keys or completing challenges. \n"
        "The door serves as a progress point and may lead to more complex puzzles or stronger enemies."},

        {"RockXPL", "Rock: A natural or environmental barrier.\n"
        "While it may not be as dangerous as other obstacles,\n"
        "it can still block pathways or hinder the player's progress.\n"
        "Rocks may also be used to hide secrets or be part of environmental puzzles."},

        {"StupidGuardXPL", "Stupid_Guard: A less intelligent enemy that behaves erratically,\n"
        "often following a random path.\n"
        "While not as challenging as the smart guard,\n"
        "these guards can still pose a threat if the player isn't paying attention,\n"
        "as they may block paths or accidentally alert more dangerous enemies."},

        {"PresentXPL",   "Present: You can get a random 'help' and there are five options:\n"
        "A: freeze the guard for five seconds.\n"
        "B: gain one life (max four life during level).\n"
        "C: remove one random guard.\n"
        "D: gain extra time.\n"},

        {"AboutGame","In this game, you control a robot navigating through various levels filled with obstacles and enemies."
        " Your goal is to overcome these \n challenges, avoid traps, and find your way to the next area."
        " As the player, you can use different tools and abilities to assist  in your \n journey, "
        "but you'll need to think strategically to avoid being caught or hindered by guards,"
        " walls, or other hazards.  With multiple \n levels and increasing difficulty,"
        " the game tests your problem-solving skills and reaction times. Can you \n guide the robot through all the challenges and escape to safety?"},
    };
}






void ResourceManager::loadTextures() {
    std::vector<std::string> textureFiles = {
        "wall.png", "rock.png", "rick_guard.png", "door.png", "empty.png",
        "bomb.png", "present.png", "arrow.png", "bombXPLD.png", "clock.png",
        "explosion.png", "heart.png", "helpBackground.png", "menu.png",
        "mute.png", "Robot.png", "RobotXPL.png", "robot_spritesheet.png",
        "Rock.png", "scary_guard_spritesheet.png", "smartGuardSprite.png",
        "timer.png", "unmute.png", "background1.png", "background2.png",
        "background3.png", "background4.png", "background5.png",
        "background6.png", "lost_life_screen.png", "guard_morty.png", "Coin.png" ,
        "ESC.png"
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
    // Log the missing key for debugging
    std::cerr << "Sound not found: " << key << std::endl;
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

const std::string& ResourceManager::getString(const std::string& key)
{
    std::cout << key << std::endl;
    auto it = m_HelpXPL.find(key);
    if (it != m_HelpXPL.end()) {
        return it->second;
    }
    throw std::runtime_error("String not found: " + key);
}


void ResourceManager::addText(const std::string& key, const sf::Text& text) {
    m_texts[key] = text;
}

