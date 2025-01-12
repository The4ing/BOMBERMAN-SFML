#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
    m_mainMenu(&m_window, 0),             // Initialize MainMenuDisplay with window and dummy game ID
    m_gameScreen(&m_window),              // Initialize GameDisplay with window
    m_settingsScreen(&m_window)           // Initialize SettingsDisplay with window
{
    // Additional setup if necessary
}

void GameManager::startGame()
{
	m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN", sf::Style::Titlebar | sf::Style::Close);

    // Example: Run the main menu

    while (m_window.isOpen()) {
        m_mainMenu.Run();
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        m_window.clear();
        // Add rendering code here
        m_window.display();
    }
	
}


