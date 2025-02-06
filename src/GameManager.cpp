#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

// Constructor
GameManager::GameManager()
    : m_window(sf::VideoMode(static_cast<int>(WINDOW_WIDTH), static_cast<int>(WINDOW_HEIGHT)), "BOMBERMAN"),
    m_robotLives(3),
    m_pause(false),
    m_arrowKeyPressed(false),
    m_robotDirection(STAND),
    m_mainMenu(&m_window, 0),
    m_gameScreen(&m_window),
    m_settingsScreen(&m_window),
    m_currentLevel(1) // Start from Level 1
{
    ResourceManager& resourceManager = ResourceManager::getInstance();
    m_muteButtonSprite.setTexture(resourceManager.getTexture("mute.png")); // Default mute icon
    m_muteButtonSprite.setPosition(WINDOW_WIDTH - 80, 20); // Top-right corner

}


void GameManager::newGame() {
    m_currentLevel = 1;  // Reset to level 1
    m_robotLives = 3;
    m_pause = false;

    std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";
    m_board.loadFromFile(levelFile, m_currentLevel);

    std::cout << "New game started at " << levelFile << "!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    m_mainMenu.Run();
    startGame();
}
void GameManager::startGame() {



    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sprite screenSprite(resourceManager.getTexture("lost_life_screen.png"));

    std::string backgroundImage = "background" + std::to_string(m_currentLevel) + ".png";

    m_backgroundSprite.setTexture(resourceManager.getTexture(backgroundImage)); // Assign the texture to the sprite
    m_gameMusic = "startGame";
    if (m_currentLevel == 6) { // 6  = BOSS_LEVEL
        m_gameMusic = "bossGame";
    }
    sf::Music& gamePlay = resourceManager.getMusic(m_gameMusic);
    gamePlay.setLoop(false);

    // m_menuMusic.setVolume(50);
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

        if (!isWindowFocused) continue; // Skip updates when window is unfocused

        //std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";
        //m_board.loadPresent(levelFile);

        sf::Time deltaTime = clock.restart();
        gameState = m_board.update(deltaTime.asSeconds()); // Handles pause & game logic
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
            darkOverlay.setFillColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black

            // Load pause screen image
            ResourceManager& resourceManager = ResourceManager::getInstance();
            sf::Sprite pauseSprite(resourceManager.getTexture("pauseSign.png"));

            // Center the pause image
            pauseSprite.setPosition(
                (WINDOW_WIDTH - pauseSprite.getGlobalBounds().width) / 2,
                (WINDOW_HEIGHT - pauseSprite.getGlobalBounds().height) / 2
            );

            // Draw pause screen
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
        if (m_board.isLevelComplete()) {  // Check if the player completed the level
            gamePlay.stop();
            screenSprite.setTexture(resourceManager.getTexture("levelComplete.png"));
            sf::Sound& levelCompleteSound = resourceManager.getSound("levelComplete");
            levelCompleteSound.setVolume(25);
            levelCompleteSound.play();
            m_window.draw(screenSprite);
            m_window.display();
            sf::sleep(sf::seconds(3));
            loadNextLevel();  // Load the next level
        }
        processGameEvents(); //can handle here keys and mouse

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
            m_board.handleInput(event.key.code, true);
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

        case sf::Event::KeyReleased:
            m_board.handleInput(event.key.code, false);
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePixelPosition(event.mouseButton.x, event.mouseButton.y);
              //  sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                m_board.handleMouseClick(m_window, mousePixelPosition);
            }
            break;


        default:
            break;
        }
    }
}


//void GameManager::setRobotPosition() {
//    robot->setPosition(m_board.getRobotScreenPosition(m_window).x,
//        m_board.getRobotScreenPosition(m_window).y);
//
//}

char GameManager::getSingleKeyPress() {
    //while (true) {
    //    for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; ++key) {
    //        if (sf::Keyboard::
    //            (static_cast<sf::Keyboard::Key>(key))) {
    //            return static_cast<char>('A' + (key - sf::Keyboard::A)); // Convert to uppercase letter
    //        }
    //    }
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return '\x1B'; // ESC key
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return ' '; // Space key
    //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) return '\n'; // Enter key
    //}
    return 'c';
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
    ////while (1);

    //// Reset game state
    m_robotLives = 3;
    m_pause = false;

    //// Restart game with the new level
    startGame();
}
