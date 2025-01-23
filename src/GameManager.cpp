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
    m_settingsScreen(&m_window) {
    m_board.loadTextures();
}

void GameManager::newGame() {
    m_cellSize = m_board.getCellSize();
    m_robotLives = 3;
    m_pause = false;
    m_board.loadFromFile("level1.txt");
    std::cout << "New game started!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
      m_mainMenu.Run();
       startGame();
}

void GameManager::startGame() {
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        processGameEvents();

        float deltaTimeInSeconds = deltaTime.asSeconds();
        m_board.update(deltaTimeInSeconds); // Update Board (handles Robot internally)

        // Render the game
        m_window.clear();
        m_board.display(m_window); // Board handles all drawing
        m_window.display();
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
