#include "MainMenuDisplay.h"
#include <iostream>

// Constructor
MainMenuDisplay::MainMenuDisplay(sf::RenderWindow* window, int game)
    : m_window(window), m_game(game), m_state(MAIN_MENU) {
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



    m_helpText.setFont(m_font);
    m_helpText.setString("Use the arrow keys to direct Bomberman in any one of the four cardinal directions.\nUse the B button : Press the B button to drop a bomb on the tile that Bomberman is currently standing on.\nthe bomb will self destruct after four seconds\nPress ESC to return to the menu.");
    m_helpText.setCharacterSize(30);
    m_helpText.setFillColor(sf::Color::White);
    m_helpText.setPosition(50, 50); // Adjust position as needed
}

// Configure button with hover background
void MainMenuDisplay::configureButton(sf::Text& button, const std::string& label, const sf::Color& color, int yOffset) {
    float windowWidth = m_window->getSize().x;
    float windowHeight = m_window->getSize().y;

    button.setFont(m_font);
    button.setString(label);
    button.setCharacterSize(40);
    button.setFillColor(color);

    // Center the button
    sf::FloatRect bounds = button.getLocalBounds();
    button.setOrigin(bounds.width / 2, bounds.height / 2);
    button.setPosition(
        windowWidth / 2,
        (windowHeight / 2) + yOffset
    );
}

// Show main menu or help screen
void MainMenuDisplay::show() {
    m_window->clear(sf::Color::Black);

    if (m_state == MAIN_MENU) {
        m_window->draw(m_backgroundSprite);

        // Draw buttons
        m_window->draw(m_startButton);
        m_window->draw(m_helpButton);
        m_window->draw(m_exitButton);
    }
    else if (m_state == HELP_SCREEN) {
        m_window->draw(m_backgroundSprite);
        m_window->draw(m_helpText);
    }

    m_window->display();
}

// Handle user input
int MainMenuDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape && m_state == HELP_SCREEN) {
                m_state = MAIN_MENU;
            }
        }

        if (event.type == sf::Event::MouseMoved) {
            handleHover(sf::Mouse::getPosition(*m_window));
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (handleButtonClick(sf::Mouse::getPosition(*m_window)) == START_GAME) {
                    return START_GAME;
                }
            }
        }
    }
    return 0;
}

// Handle button clicks
int MainMenuDisplay::handleButtonClick(sf::Vector2i mousePosition) {
    if (m_startButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Start Game button clicked!" << std::endl;
        menuMmusic.stop();
        return START_GAME;
    }
    else if (m_helpButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Help button clicked!" << std::endl;
        m_state = HELP_SCREEN;
    }
    else if (m_exitButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        std::cout << "Exit button clicked!" << std::endl;
        m_window->close();
    }
    return 0;
}

// Handle hover effects
void MainMenuDisplay::handleHover(sf::Vector2i mousePosition) {
    auto setHoverEffect = [&](sf::Text& button) {
        if (button.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
            button.setFillColor(sf::Color::Red);
            button.setScale(1.1f, 1.1f);
        }
        else {
            button.setFillColor(sf::Color::Black);
            button.setScale(1.0f, 1.0f);
        }
        };

    setHoverEffect(m_startButton);
    setHoverEffect(m_helpButton);
    setHoverEffect(m_exitButton);
}

// Main loop
void MainMenuDisplay::Run() {
    menuMmusic.setLoop(true);
    menuMmusic.setVolume(50.0f);
    menuMmusic.play();

    while (m_window->isOpen()) {
        if (handleInput() == START_GAME) break;
        show();
    }
}
