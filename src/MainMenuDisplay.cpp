#include "MainMenuDisplay.h"
#include <iostream>

// Constructor
MainMenuDisplay::MainMenuDisplay(sf::RenderWindow* window, int game)
    : m_window(window), m_game(game), m_state(MAIN_MENU) { // Initialize state
    // Load music file
    if (!menuMmusic.openFromFile("menuMusic.ogg")) {
        std::cerr << "Error: Could not load music file!" << std::endl;
    }

    // Load fonts and textures
    if (!m_font.loadFromFile("PixelFontBlack.otf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    if (!m_backgroundTexture.loadFromFile("menu.png")) {
        std::cerr << "Error loading background image!" << std::endl;
    }
    m_backgroundSprite.setTexture(m_backgroundTexture);

    if (!m_helpBackgroundTexture.loadFromFile("helpBackground.png")) {
        std::cerr << "Error loading help background image!" << std::endl;
    }

    // Configure main menu buttons
    configureButton(m_startButton, "Start Game", sf::Color::Black, -100);
    configureButton(m_helpButton, "Help", sf::Color::Black, 0);
    configureButton(m_exitButton, "Exit", sf::Color::Black, 100);

    // Configure help text
    m_helpText.setFont(m_font);
    m_helpText.setString("Use the arrow keys to direct Bomberman in any one of the four cardinal directions.\nUse the B button : Press the B button to drop a bomb on the tile that Bomberman is currently standing on.\nthe bomb will self destruct after four seconds\nPress ESC to return to the menu.");
    m_helpText.setCharacterSize(30);
    m_helpText.setFillColor(sf::Color::White);
    m_helpText.setPosition(50, 50); // Adjust position as needed
}

void MainMenuDisplay::configureButton(sf::Text& button, const std::string& label, const sf::Color& color, int yOffset) {
    float windowWidth = m_window->getSize().x;
    float windowHeight = m_window->getSize().y;

    button.setFont(m_font);
    button.setString(label);
    button.setCharacterSize(40);
    button.setFillColor(color);
    sf::FloatRect bounds = button.getGlobalBounds();
    button.setPosition(
        (windowWidth - bounds.width) / 2,
        (windowHeight / 2) + yOffset
    );
}

// Show the main menu or help screen
void MainMenuDisplay::show() {
    m_window->clear(sf::Color::Black);

    if (m_state == MAIN_MENU) {
        m_backgroundSprite.setTexture(m_backgroundTexture); // Reset texture to main menu background
        m_window->draw(m_backgroundSprite);
        m_window->draw(m_startButton);
        m_window->draw(m_helpButton);
        m_window->draw(m_exitButton);
    }
    else if (m_state == HELP_SCREEN) {
        m_backgroundSprite.setTexture(m_helpBackgroundTexture); // Set texture to help background
        m_window->draw(m_backgroundSprite);
        m_window->draw(m_helpText);
    }

    m_window->display();
}


// Handle input
void MainMenuDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape && m_state == HELP_SCREEN) {
                m_state = MAIN_MENU; // Return to main menu
            }
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
        menuMmusic.stop();
    }
    else if (m_helpButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Help button clicked!" << std::endl;
        m_state = HELP_SCREEN; // Change state to help screen
    }
    else if (m_exitButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Exit button clicked!" << std::endl;
        m_window->close();
    }
}

// Main loop
void MainMenuDisplay::Run() {
    menuMmusic.setLoop(true);
    menuMmusic.setVolume(50.0f);
    menuMmusic.play();

    while (m_window->isOpen()) {
        handleInput();
        show();
    }
}
