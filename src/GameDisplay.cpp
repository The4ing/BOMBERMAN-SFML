#include "GameDisplay.h"
#include <iostream>

// Constructor
GameDisplay::GameDisplay(sf::RenderWindow* window)
    : m_window(window) {}

// Show the game screen
void GameDisplay::show() {
    m_window->clear();
    std::cout << "Displaying Game Screen..." << std::endl;
    m_window->display();
}

// Handle input in the game
int GameDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
        // Add game-specific input handling
    }
    return 0;
}
