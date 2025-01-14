#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "Board.h"

GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
    m_mainMenu(&m_window, 0),             // Initialize MainMenuDisplay with window and dummy game ID
    m_gameScreen(&m_window),              // Initialize GameDisplay with window
    m_settingsScreen(&m_window)           // Initialize SettingsDisplay with window

{
    m_board.loadFromFile("level1.txt");
    m_board.loadTextures();
}

void GameManager::newGame()
{
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    m_mainMenu.Run();
    startGame();
}


void GameManager::startGame() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::Resized) {
                // Adjust the view when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_window.setView(sf::View(visibleArea));
            }
            if (event.key.code == sf::Keyboard::Escape) {
                m_mainMenu.Run();
            }
        }

        m_window.clear();
        m_board.display(m_window);
        m_window.display();
    }
}


bool GameManager::loadLevel(const std::string& fileName) {
    return true;
}
