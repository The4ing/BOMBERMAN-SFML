#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

GameManager::GameManager()
    : m_window(sf::VideoMode(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), "BOMBERMAN"),
  //  m_arrowKeyPressed(false),
    m_mainMenu(&m_window, 0),
    m_currentLevel(START_GAME)
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    m_muteButtonSprite.setTexture(resourceManager.getTexture("mute.png")); 
    m_muteButtonSprite.setPosition(WINDOW_WIDTH - 80, 20); 

}

void GameManager::newGame() {
    m_currentLevel = START_GAME;  
    std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";
    m_board.loadFromFile(levelFile, m_currentLevel);
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    m_mainMenu.Run();
    startGame();
}

void GameManager::startGame() {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sprite screenSprite(resourceManager.getTexture("lost_life_screen.png"));
    std::string backgroundImage = "background" + std::to_string(m_currentLevel) + ".png";
    m_backgroundSprite.setTexture(resourceManager.getTexture(backgroundImage)); 
    m_gameMusic = "startGame";
    if (m_currentLevel == BOSS_LEVEL) { 
        m_gameMusic = "bossGame";
    }
    sf::Music& gamePlay = resourceManager.getMusic(m_gameMusic);
    gamePlay.setLoop(false);
    gamePlay.play();
    m_window.clear();
    sf::Clock clock;
    int gameState = 0;
    bool isWindowFocused = true;
    m_board.startTimer();

    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                m_window.close();
                return;
            case sf::Event::LostFocus:
                isWindowFocused = false;
                break;
            case sf::Event::GainedFocus:
                isWindowFocused = true;
                break;
            default:
                break;
            }
        }

        if (!isWindowFocused) continue; 

        sf::Time deltaTime = clock.restart();
        gameState = m_board.update(deltaTime.asSeconds());
        if (gameState == LOST_GAME) {
            gamePlay.stop();
            screenSprite.setTexture(resourceManager.getTexture("gameOver.png"));
            sf::Sound& gameOverSound = resourceManager.getSound("gameOver");
            gameOverSound.setVolume(25);
            gameOverSound.play();
            sf::sleep(sf::seconds(3));
            m_window.draw(screenSprite);
            m_window.display();
            sf::sleep(sf::seconds(4));
            m_board.reset();
            newGame();
        }

        else if (m_currentLevel == 6 && m_board.isLevelComplete()) {
            gamePlay.stop();
            screenSprite.setTexture(resourceManager.getTexture("won.png"));
            sf::Sound& wonSound = resourceManager.getSound("won");
            wonSound.setVolume(25);
            wonSound.play();
            m_window.draw(screenSprite);
            m_window.display();
            sf::sleep(sf::seconds(13));

            m_board.reset();
            newGame();
        }

        else if (gameState == LOST_LIFE) {
            gamePlay.stop();
            sf::Sound& levelCompleteSound = resourceManager.getSound("died");
            levelCompleteSound.setVolume(25);
            levelCompleteSound.play();
            sf::sleep(sf::seconds(1));

            m_window.draw(screenSprite);
            m_window.display();

            sf::sleep(sf::seconds(2));
            gamePlay.play();
            m_window.clear();
            m_window.draw(m_backgroundSprite);
            m_board.display(m_window);
            m_window.display();
        }

        else if (gameState == TIMES_UP) {
            gamePlay.stop();
            screenSprite.setTexture(resourceManager.getTexture("timesUp.png"));
            sf::Sound& timesUpSound = resourceManager.getSound("timesUp");
            timesUpSound.setVolume(25);
            timesUpSound.play();
            m_window.draw(screenSprite);
            m_window.display();
            sf::sleep(sf::seconds(4));
            m_currentLevel--;
            loadNextLevel();
        }

        if (m_board.isPaused()) {
            // Darken the window
            sf::RectangleShape darkOverlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
            darkOverlay.setFillColor(sf::Color(0, 0, 0, 150)); 
            ResourceManager& resourceManager = ResourceManager::getInstance();
            sf::Sprite pauseSprite(resourceManager.getTexture("pauseSign.png"));

            pauseSprite.setPosition(
                (WINDOW_WIDTH - pauseSprite.getGlobalBounds().width) / 2,
                (WINDOW_HEIGHT - pauseSprite.getGlobalBounds().height) / 2
            );

            m_window.clear();
            m_window.draw(m_backgroundSprite);
            m_board.display(m_window);
            m_window.draw(darkOverlay);
            m_window.draw(pauseSprite);
            m_window.display();
        }

        else {
            m_window.clear();
            m_window.draw(m_backgroundSprite);
            m_board.display(m_window);
            m_window.display();
        }

        if (m_board.isLevelComplete()) {
            gamePlay.stop();
            screenSprite.setTexture(resourceManager.getTexture("levelComplete.png"));
            sf::Sound& levelCompleteSound = resourceManager.getSound("levelComplete");
            levelCompleteSound.setVolume(25);
            levelCompleteSound.play();
            m_window.draw(screenSprite);
            m_window.display();
            sf::sleep(sf::seconds(3));
            loadNextLevel(); 
        }
        processGameEvents();

    }
}

void GameManager::processGameEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {

        case sf::Event::Closed:
            m_window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
                ResourceManager& resourceManager = ResourceManager::getInstance();
                sf::Music& gamePlay = resourceManager.getMusic(m_gameMusic);
                gamePlay.stop();
                m_board.reset();
                newGame();
            }
            if (event.key.code == sf::Keyboard::P) {
                m_board.togglePause();
            }
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePixelPosition(event.mouseButton.x, event.mouseButton.y);
                m_board.handleMouseClick(m_window, mousePixelPosition);
            }
            break;
        default:
            break;
        }
    }
}

void GameManager::loadNextLevel() {
  
    m_currentLevel++;  // Move to the next level

    // Generate the filename based on level number
    std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";

    // Try loading the new level file
    if (!m_board.loadFromFile(levelFile, m_currentLevel)) {
        std::cerr << "Error: Could not load " << levelFile << ". Restarting at Level 1." << std::endl;
        m_currentLevel = 1; // Reset to first level if not found
        levelFile = "level1.txt";
        m_board.loadFromFile(levelFile, m_currentLevel);
    }

    std::cout << "Loaded " << levelFile << std::endl;
    startGame();
}
