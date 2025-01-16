#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "Robot.h" // Include the Robot class

// Constructor
GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
    m_robotLives(3),
    m_pause(false),
    m_arrowKeyPressed(false),
    m_robotDirection(STAND), // Default robot direction
    m_mainMenu(&m_window, 0), // Initialize MainMenuDisplay with window and dummy game ID
    m_gameScreen(&m_window),  // Initialize GameDisplay with window
    m_settingsScreen(&m_window), // Initialize SettingsDisplay with window
    m_robot() // Initialize Robot
{
    m_board.loadFromFile("level1.txt");
    m_board.loadTextures();

    // Set the robot's initial position
    m_robot.setPosition(100.f, 100.f); // Adjust starting position as needed
}

void GameManager::newGame() {
    m_robotLives = 3;
    m_pause = false;
    m_board.loadFromFile("level1.txt"); // Reload the level
    m_robot.setPosition(100.f, 100.f); // Reset robot's position
    std::cout << "New game started!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    m_mainMenu.Run();
    startGame();
}

void GameManager::startGame() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart(); // Calculate deltaTime for smooth updates

        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                m_robot.handleInput(event.key.code, event.type == sf::Event::KeyPressed);
            }
        }

        // Update robot and other game elements
        m_robot.update(deltaTime.asSeconds());

        // Render the game
        m_window.clear();
        m_board.display(m_window); // Draw the board
        m_robot.draw(m_window);   // Draw the robot
        m_window.display();
    }
}


bool GameManager::loadLevel(const std::string& fileName) {
    //return m_board.loadFromFile(fileName); // Update this if level loading requires specific logic
    return true;
}

void GameManager::processGameEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Escape) {
                m_robotLives = 3;
                m_mainMenu.Run();
                return;
            }
            if (event.key.code == sf::Keyboard::X) {
                std::cout << "Bomb dropped!\n"; // Logic for dropping a bomb
            }
            else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
                event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                handleMoveKeys(event.key.code, true);
            }
        } break;

        case sf::Event::KeyReleased: {
            if (event.key.code == sf::Keyboard::X)
                break;

            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
                event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                handleMoveKeys(event.key.code, false);
            }
        } break;

        default:
            break;
        }
    }
}

void GameManager::handleMoveKeys(sf::Keyboard::Key key, const bool isPressed) {
    if (!m_pause) {
        // Delegate movement input to the Robot class
        m_robot.handleInput(key, isPressed);
        m_arrowKeyPressed = isPressed;
    }
}
