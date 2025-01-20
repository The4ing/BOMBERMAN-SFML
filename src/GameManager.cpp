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
    setRobotPosition();
}

void GameManager::newGame() {
    m_cellSize = m_board.getCellSize();
    m_robotLives = 3;
    m_pause = false;
    m_board.loadFromFile("level1.txt"); // Reload the level
    //  m_robot.setPosition(100.f, 100.f); // Reset robot's position

    std::cout << "New game started!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    m_mainMenu.Run();
    startGame();
}

void GameManager::startGame() {
    float frameWidth = m_window.getSize().x * 0.8f;
    float frameHeight = m_window.getSize().y * 0.8f;
    float offsetX = (m_window.getSize().x - frameWidth) / 2.0f;
    float offsetY = (m_window.getSize().y - frameHeight) / 2.0f;

    sf::Clock clock;
    sf::Vector2f robotScreenPos = m_board.getRobotScreenPosition(m_window);
    std::cout << "Robot is at screen position: ("
        << robotScreenPos.x << ", " << robotScreenPos.y << ")\n";


    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float deltaTimeInSeconds = deltaTime.asSeconds();

        processGameEvents();
        int i = (((m_robot.getCurrentCell().x - offsetX + (m_cellSize.x / 2)) / m_cellSize.x));
        int j = ((m_robot.getCurrentCell().y - offsetY + (m_cellSize.x / 2)) / (m_cellSize.y));
        // Handle active keys for movement
        if (!m_pause) {
            for (const auto& key : m_activeKeys) {
                if (m_board.isWalkable(i, j)) {
                    m_robot.handleInput(key, true);
                }
            }
        }
        std::cout << m_cellSize.x << " " << m_cellSize.y << std::endl;
        // Update robot and other game elements
        m_robot.update(deltaTime.asSeconds());
        m_board.callUpdateToolbar(deltaTimeInSeconds);
        std::cout <<"offset" << offsetX << " " << offsetY << std::endl;
        std::cout << "this is cell size" << m_cellSize.x << "and" << m_cellSize.y << std::endl;

        //std::cout << "im in cell" << i << " and " << j << std::endl;

        std::cout << "im in cell" << (static_cast<int>((m_robot.getCurrentCell().x - offsetX + (m_cellSize.x / 2)) / m_cellSize.x)) << " and " << static_cast<int>(((m_robot.getCurrentCell().y - offsetY + (m_cellSize.y / 2)) / (m_cellSize.y))) << std::endl;
        std::cout << "is walkable: " << m_board.isWalkable(static_cast<int>(((m_robot.getCurrentCell().x - offsetX + (m_cellSize.x / 2)) / m_cellSize.x)), static_cast<int>(((m_robot.getCurrentCell().y - offsetY + (m_cellSize.x / 2)) / (m_cellSize.y)))) << std::endl;
        std::cout << " this is cell " << ((m_robot.getCurrentCell().x - offsetX + (m_cellSize.x / 2)) / m_cellSize.x) << " " << ((m_robot.getCurrentCell().y - offsetY + (m_cellSize.y / 2)) / (m_cellSize.y)) << std::endl;


         // Render the game
        m_window.clear();
        m_board.draw(m_window);
        m_board.display(m_window);
        m_robot.draw(m_window);
        m_window.display();
        //// Draw all elements
   //for (size_t pos = 0; pos < m_board.getHeartCount(); ++pos) {
   //    drawDrawable(HEART, pos);
   //}

   //drawDrawable(CLOCK, 0);

   //drawDrawable(ARROW, 0);

   //drawDrawable(BAR, 0);

   //m_window.draw(m_board.GetText());
   //std::cout << "type1" << std::endl;
   //// Draw the robot and board
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

        case sf::Event::KeyPressed:
            m_activeKeys.insert(event.key.code); // Add key to active set
            m_robot.handleInput(event.key.code, true); // Notify robot of key press
            if (event.key.code == sf::Keyboard::Escape) {
                m_robotLives = 3;
                m_mainMenu.Run();
                return;
            }
            if (event.key.code == sf::Keyboard::X) {
                std::cout << "Bomb dropped!\n";
            }
            break;

        case sf::Event::KeyReleased:
            m_activeKeys.erase(event.key.code); // Remove key from active set
            m_robot.handleInput(event.key.code, false); // Notify robot of key release
            break;

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


void GameManager::setRobotPosition() {
    m_robot.setPosition(m_board.getRobotScreenPosition(m_window).x, m_board.getRobotScreenPosition(m_window).y);
}
