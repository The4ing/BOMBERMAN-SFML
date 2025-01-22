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
    m_board.loadFromFile("level1.txt");
    m_board.loadTextures();

    // Add a Robot instance to m_movingObjects
    m_movingObjects.push_back(std::make_unique<Robot>());

    setRobotPosition();
}

void GameManager::newGame() {
    m_cellSize = m_board.getCellSize();
    m_robotLives = 3;
    m_pause = false;
    m_board.loadFromFile("level1.txt");

    //auto robot = dynamic_cast<Robot*>(m_movingObjects[0].get());
    //if (robot) {
    //    robot->setPosition(100.f, 100.f); // Reset robot's position
    //}

    std::cout << "New game started!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
      m_mainMenu.Run();
       startGame();
}

void GameManager::startGame() {
    sf::Clock clock;

    float frameWidth = m_window.getSize().x * 0.8f;
    float frameHeight = m_window.getSize().y * 0.8f;
    float offsetX = (m_window.getSize().x - frameWidth) / 2.0f;
    float offsetY = (m_window.getSize().y - frameHeight) / 2.0f;

   
    sf::Vector2f robotScreenPos = m_board.getRobotScreenPosition(m_window);
   /* std::cout << "Robot is at screen position: ("
        << robotScreenPos.x << ", " << robotScreenPos.y << ")\n";*/

   /* int i = (((robot->getCurrentCell().x - offsetX + (m_cellSize.x / 2)) / m_cellSize.x));
    int j = ((robot->getCurrentCell().y - offsetY + (m_cellSize.x / 2)) / (m_cellSize.y));*/

    while (m_window.isOpen()) {
       

        sf::Time deltaTime = clock.restart();
        float deltaTimeInSeconds = deltaTime.asSeconds();
        processGameEvents();

      
        // Update all moving objects
        for (auto& object : m_movingObjects) {

            auto robot = dynamic_cast<Robot*>(m_movingObjects[0].get());
            if (robot) {
                


              robot->update(deltaTime.asSeconds());
                
                        
            }
           
        }
        m_board.callUpdateToolbar(deltaTimeInSeconds);

        // Render the game
        m_window.clear();
        m_board.draw(m_window);
        m_board.display(m_window);
        for (const auto& object : m_movingObjects) {
            object->draw(m_window);
        }

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
            m_activeKeys.insert(event.key.code);
            for (const auto& object : m_movingObjects) {
                object->handleInput(event.key.code, true);
            }
            if (event.key.code == sf::Keyboard::Escape) {
                m_mainMenu.Run();
                return;
            }
            if (event.key.code == sf::Keyboard::X) {
                std::cout << "Bomb dropped!\n";
            }
            break;

        case sf::Event::KeyReleased:
            m_activeKeys.erase(event.key.code);
            for (const auto& object : m_movingObjects) {
                object->handleInput(event.key.code, false);
            }
            break;

        default:
            break;
        }
    }

    // Handle active keys for movement
    auto robot = dynamic_cast<Robot*>(m_movingObjects[0].get());
    if (robot) {
        for (const auto& key : m_activeKeys) {
            robot->handleInput(key, true);
        }
    }
}



void GameManager::setRobotPosition() {
    auto robot = dynamic_cast<Robot*>(m_movingObjects[0].get());
    if (robot) {
        robot->setPosition(m_board.getRobotScreenPosition(m_window).x,
            m_board.getRobotScreenPosition(m_window).y);
    }
}
