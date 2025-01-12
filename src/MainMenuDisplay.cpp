#include "MainMenuDisplay.h"
#include <iostream>

// Constructor
// Constructor
// Constructor
MainMenuDisplay::MainMenuDisplay(sf::RenderWindow* window, int game)
    : m_window(window), m_game(game) {
    // Load font
    if (!m_font.loadFromFile("PixelFontBlack.otf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Load background texture
    if (!m_backgroundTexture.loadFromFile("menu.png")) {
        std::cerr << "Error loading background image!" << std::endl;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);
    m_backgroundSprite.setScale(
        static_cast<float>(m_window->getSize().x) / m_backgroundTexture.getSize().x,
        static_cast<float>(m_window->getSize().y) / m_backgroundTexture.getSize().y
    );

    // Calculate button positions
    float windowWidth = m_window->getSize().x;
    float windowHeight = m_window->getSize().y;

    // Configure "Start Game" button
    m_startButton.setFont(m_font);
    m_startButton.setString("Start Game");
    m_startButton.setCharacterSize(40);
    m_startButton.setFillColor(sf::Color::Black);
    sf::FloatRect startButtonBounds = m_startButton.getGlobalBounds();
    m_startButton.setPosition(
        (windowWidth - startButtonBounds.width) / 2,
        windowHeight / 2 - 100
    );

    // Configure "Help" button
    m_helpButton.setFont(m_font);
    m_helpButton.setString("Help");
    m_helpButton.setCharacterSize(40);
    m_helpButton.setFillColor(sf::Color::Black);
    sf::FloatRect helpButtonBounds = m_helpButton.getGlobalBounds();
    m_helpButton.setPosition(
        (windowWidth - helpButtonBounds.width) / 2,
        windowHeight / 2
    );

    // Configure "Exit" button
    m_exitButton.setFont(m_font);
    m_exitButton.setString("Exit");
    m_exitButton.setCharacterSize(40);
    m_exitButton.setFillColor(sf::Color::Black);
    sf::FloatRect exitButtonBounds = m_exitButton.getGlobalBounds();
    m_exitButton.setPosition(
        (windowWidth - exitButtonBounds.width) / 2,
        windowHeight / 2 + 100
    );
}

// Show the main menu
void MainMenuDisplay::show() {
    m_window->clear(sf::Color::Black); // Clear with a black background

    // Draw the background
    m_window->draw(m_backgroundSprite);

    // Draw buttons
    m_window->draw(m_startButton);
    m_window->draw(m_helpButton);
    m_window->draw(m_exitButton);

    m_window->display();
}


// Handle input in the main menu
void MainMenuDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                handleButtonClick(sf::Mouse::getPosition(*m_window));
            }
        }
    }
}

// Handle button clicks
void MainMenuDisplay::handleButtonClick(sf::Vector2i mousePosition) {
    if (m_startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Start Game button clicked!" << std::endl;
        // Logic to transition to the game display
    }
    else if (m_helpButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Help button clicked!" << std::endl;
        // Show help information
    }
    else if (m_exitButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Exit button clicked!" << std::endl;
        m_window->close(); // Exit the application
    }
}

// Main loop for the main menu
void MainMenuDisplay::Run() {
    while (m_window->isOpen()) {
        handleInput();
        show();
    }
}


