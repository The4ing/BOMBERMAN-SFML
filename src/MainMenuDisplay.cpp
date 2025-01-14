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

     //this is for explanation how each button works 
 ////add
 //// Configure hover area
 //m_robotArea.setSize(sf::Vector2f(300.f, 50.f));
 //m_robotArea.setPosition(100.f, 150.f); // Adjust position as needed
 //m_robotArea.setFillColor(sf::Color::Transparent); // No color but can debug with borders

 //// Configure tooltip
 //m_hoverExplanationText.setFont(m_font);
 //m_hoverExplanationText.setCharacterSize(20);
 //m_hoverExplanationText.setFillColor(sf::Color::White);
 //m_hoverExplanationText.setString("ROBOT"); // Empty by default    
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

        ////add
//sf::Vector2f m_robotAreaPosition(100.f, 200.f); // Hover area position
//sf::Vector2f m_robotAreaSize(150.f, 100.f);    // Hover area size

//// Load texture for debugging or visualization
//sf::Texture debugTexture;
//if (!debugTexture.loadFromFile("robot.png")) {
//    std::cerr << "Error: Could not load hover debug image!" << std::endl;
//}

//// Create a sprite to represent the hover area
//sf::Sprite debugSprite;
//debugSprite.setTexture(debugTexture);

//// Adjust the sprite to fit the hover area (optional)
//debugSprite.setPosition(m_robotAreaPosition.x, m_robotAreaPosition.y);
//debugSprite.setScale(
//    m_robotAreaSize.x / debugTexture.getSize().x,
//    m_robotAreaSize.y / debugTexture.getSize().y
//);

//// Draw the sprite to the window
//m_window->draw(debugSprite);

//if (!m_hoverExplanationText.getString().isEmpty()) {
//    m_window->draw(m_hoverExplanationText);
//}
    }

    m_window->display();
}


// Handle input
int MainMenuDisplay::handleInput() {
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
                if (handleButtonClick(sf::Mouse::getPosition(*m_window)) == START_GAME) {
                    return START_GAME;
                }
            }
        }
    }
    //ddd
    //if (m_state == HELP_SCREEN) {
    //    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window);

    //    // Check hover on robot area
    //    if (m_robotArea.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
   //        m_hoverExplanationText.setString("The robot helps navigate through the maze.");
   //        m_hoverExplanationText.setPosition(static_cast<float>(mousePosition.x) + 15.f, static_cast<float>(mousePosition.y) + 15.f);
   //    }
   //    else {
   //        m_hoverExplanationText.setString(""); // Clear tooltip if not hovering
  //    }
   //}
    
}

// Handle button clicks
int MainMenuDisplay::handleButtonClick(sf::Vector2i mousePosition) {
    sf::Vector2f worldMousePos = m_window->mapPixelToCoords(mousePosition);

    int startGame = 0;
    if (m_startButton.getGlobalBounds().contains(worldMousePos)) {
        std::cout << "Start Game button clicked!" << std::endl;
        menuMmusic.stop();
        startGame = START_GAME;
    }
    else if (m_helpButton.getGlobalBounds().contains(worldMousePos)) {
        std::cout << "Help button clicked!" << std::endl;
        m_state = HELP_SCREEN; // Change state to help screen
    }
    else if (m_exitButton.getGlobalBounds().contains(worldMousePos)) {
        std::cout << "Exit button clicked!" << std::endl;
        m_window->close();
    }
    return startGame;
}


void MainMenuDisplay::Run() {
    menuMmusic.setLoop(false);
    menuMmusic.setVolume(50.0f);
    menuMmusic.play();

    while (m_window->isOpen()) {
        if (handleInput() == START_GAME) return;
        show();
    }
}
