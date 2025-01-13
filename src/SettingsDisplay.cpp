#include "SettingsDisplay.h"
#include <iostream>

// Constructor
SettingsDisplay::SettingsDisplay(sf::RenderWindow* window)
    : m_window(window) {}

// Show the settings screen
void SettingsDisplay::show() {
    m_window->clear();
    std::cout << "Displaying Settings Screen..." << std::endl;
    m_window->display();
}

// Handle input in the settings
int SettingsDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }
        // Add settings-specific input handling
    }
    return 0;
}
