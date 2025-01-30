#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

// Constructor
GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
    m_robotLives(3),
    m_pause(false),
    m_arrowKeyPressed(false),
    m_robotDirection(STAND),
    m_mainMenu(&m_window, 0),
    m_gameScreen(&m_window),
    m_settingsScreen(&m_window),
    m_currentLevel(1) // Start from Level 1
{
    m_board.loadTextures();
}


void GameManager::newGame() {
    m_currentLevel = 1;  // Reset to level 1
    m_robotLives = 3;
    m_pause = false;

    std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";
    m_board.loadFromFile(levelFile);

    std::cout << "New game started at " << levelFile << "!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    m_mainMenu.Run();
    startGame();
}

void GameManager::startGame() {
    sf::Clock clock;
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

        sf::Time deltaTime = clock.restart();
        m_board.update(deltaTime.asSeconds()); // Handles pause & game logic

        m_window.clear();
        m_board.display(m_window);
        m_window.display();
        if (m_board.isLevelComplete()) {  // Check if the player completed the level
            loadNextLevel();  // Load the next level
        }

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
                m_mainMenu.Run();
                return;
            }
            else if (event.key.code == sf::Keyboard::B) {
                m_board.GenerateBomb();
                loadNextLevel();  // Skip to next level
            }
            else if (event.key.code == sf::Keyboard::N) {
                loadNextLevel();  // Skip to next level
            }
            break;

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
    while (true) {
        for (int key = sf::Keyboard::A; key <= sf::Keyboard::Z; ++key) {
            if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
                return static_cast<char>('A' + (key - sf::Keyboard::A)); // Convert to uppercase letter
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return '\x1B'; // ESC key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return ' '; // Space key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) return '\n'; // Enter key
    }
}

void GameManager::loadNextLevel() {
    m_window.clear();
    //m_currentLevel++;  // Move to the next level

    //// Generate the filename based on level number
    //std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";

    //// Try loading the new level file
    //if (!m_board.loadFromFile(levelFile)) {
    //    std::cerr << "Error: Could not load " << levelFile << ". Restarting at Level 1." << std::endl;
    //    m_currentLevel = 1; // Reset to first level if not found
    //    levelFile = "level1.txt";
    //    m_board.loadFromFile(levelFile);
    //}

    //std::cout << "Loaded " << levelFile << std::endl;
    ////while (1);

    //// Reset game state
    //m_robotLives = 3;
    //m_pause = false;

    //// Restart game with the new level
    //startGame();
}
