#include "MainMenuDisplay.h"
#include <iostream>

// Constructor
// Constructor
MainMenuDisplay::MainMenuDisplay(sf::RenderWindow* window, int game)
    : m_window(window), m_game(game), m_state(MAIN_MENU) {
    // Load menu music
    if (!menuMmusic.openFromFile("menuMusic.ogg")) {
        std::cerr << "Error: Could not load menu music file!" << std::endl;
    }

    // Load button click sound
    if (!m_buttonClickBuffer.loadFromFile("ButtonMusic.ogg")) {
        std::cerr << "Error: Could not load button click sound file!" << std::endl;
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

    // Configure buttons
    configureButton(m_startButton, "Start Game", sf::Color::Black, -100);
    configureButton(m_helpButton, "Help", sf::Color::Black, 0);
    configureButton(m_exitButton, "Exit", sf::Color::Black, 100);

    // Initialize help objects
    initializeHelpObjects();

    // Configure hover explanation text
    m_hoverExplanationText.setFont(m_font);
    m_hoverExplanationText.setCharacterSize(30);
    m_hoverExplanationText.setFillColor(sf::Color::Red);

    // Configure instruction text
    m_instructionText.setFont(m_font);
    m_instructionText.setString("Hover over the pictures to see and hear their explanations.");
    m_instructionText.setCharacterSize(24);
    m_instructionText.setFillColor(sf::Color::White);
    m_instructionText.setPosition(20, 20); // Adjust the position to the top of the window
}

void MainMenuDisplay::initializeHelpObjects() {
    float windowWidth = m_window->getSize().x;
    float windowHeight = m_window->getSize().y;

    // File paths for textures
    std::vector<std::string> textureFiles = {
        "wall.png", "wall.png", "wall.png", "wall.png", "wall.png", "wall.png"
    };

    // Desired size for the help objects
    float desiredWidth = windowWidth * 0.1f;  // 10% of the window width
    float desiredHeight = windowHeight * 0.1f; // 10% of the window height

    for (size_t i = 0; i < textureFiles.size(); ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFiles[i])) {
            std::cerr << "Error loading texture: " << textureFiles[i] << std::endl;
            continue;  // Skip this object if the texture failed to load
        }

        // Store the texture in the class member
        m_textures.push_back(std::move(texture));

        // Create the sprite using the stored texture
        sf::Sprite sprite(m_textures.back());

        // Scale the sprite to the desired size
        sf::Vector2u textureSize = m_textures.back().getSize();
        float scaleX = desiredWidth / textureSize.x;
        float scaleY = desiredHeight / textureSize.y;
        sprite.setScale(std::min(scaleX, scaleY), std::min(scaleX, scaleY));

        // Positioning the sprite
        float x = windowWidth * (0.15f + (i % 3) * 0.3f); // Spread out 3 objects per row
        float y = windowHeight * (0.3f + (i / 3) * 0.3f); // Adjust vertical spacing
        sprite.setPosition(x, y);

        // Explanation text for each object
        std::string explanation;
        switch (i) {
        case 0: explanation = "Wall: An obstacle."; break;
        case 1: explanation = "Robot: The main character which needs to escape through the door!"; break;
        case 2: explanation = "Bomb: Handle with care."; break;
        case 3: explanation = "Guard: Be cautious!"; break;
        case 4: explanation = "Door: Leads to the next area."; break;
        case 5: explanation = "Rock: A simple barrier."; break;
        }

        // Store the sprite and explanation in m_helpObjects
        m_helpObjects.push_back({ sprite, explanation });
    }
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

int  MainMenuDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape && m_state == HELP_SCREEN) {
                m_state = MAIN_MENU;
                m_backgroundSprite.setTexture(m_backgroundTexture);  // Reset to main menu background
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
}

// Show function modified to ensure proper background is drawn
void MainMenuDisplay::show() {
    m_window->clear(sf::Color::Black);

    if (m_state == MAIN_MENU) {
        m_backgroundSprite.setTexture(m_backgroundTexture); // Main menu texture
        m_window->draw(m_backgroundSprite);

        m_window->draw(m_startButton);
        m_window->draw(m_helpButton);
        m_window->draw(m_exitButton);
    }
    if (m_state == HELP_SCREEN) {
        m_backgroundSprite.setTexture(m_helpBackgroundTexture); // Help background texture
        m_window->draw(m_backgroundSprite);

        // Draw instruction text
        m_window->draw(m_instructionText);

        // Draw help objects (sprites)
        for (const auto& object : m_helpObjects) {
            m_window->draw(object.first); // Draw the sprite
        }

        // Draw hover explanation text
        m_window->draw(m_hoverExplanationText);
    }

    m_window->display();
}


// Handle button clicks
int MainMenuDisplay::handleButtonClick(const sf::Vector2i mousePosition) {
    if (m_state != MAIN_MENU) {
        return 0; // Do nothing if not in the main menu
    }

    sf::Vector2f worldMousePos = m_window->mapPixelToCoords(mousePosition);
    if (m_startButton.getGlobalBounds().contains(worldMousePos)) {
        std::cout << "Start Game button clicked!" << std::endl;
        m_buttonClickSound.play();
        menuMmusic.stop();
        return START_GAME;
    }
    else if (m_helpButton.getGlobalBounds().contains(worldMousePos)) {
        std::cout << "Help button clicked!" << std::endl;
        m_buttonClickSound.play();
      
        m_state = HELP_SCREEN;

        return 0;
        
    }
    else if (m_exitButton.getGlobalBounds().contains(worldMousePos)) {
        std::cout << "Exit button clicked!" << std::endl;
        m_buttonClickSound.play();
        m_window->close();
        return 0;
    }
    return 0;
}

// Handle hover effects
void MainMenuDisplay::handleHover(const sf::Vector2i mousePosition) {
    if (m_state == MAIN_MENU) {
        sf::Vector2f worldMousePos = m_window->mapPixelToCoords(mousePosition);
        // Hover effects for main menu buttons
        auto setHoverEffect = [&](sf::Text& button) {
            if (button.getGlobalBounds().contains(worldMousePos)) {
                button.setFillColor(sf::Color::Red);
                button.setScale(1.2f, 1.23f);
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
    else if (m_state == HELP_SCREEN) {
        bool hovered = false;

        for (const auto& object : m_helpObjects) {
            if (object.first.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                m_hoverExplanationText.setString(object.second);
                m_hoverExplanationText.setPosition(mousePosition.x + 15, mousePosition.y + 15);
                hovered = true;
                break;
            }
        }

        if (!hovered) {
            m_hoverExplanationText.setString(""); // Hide explanation if not hovering
        }
    }
}

// Main loop
void MainMenuDisplay::Run() {
    menuMmusic.setLoop(true);
    menuMmusic.setVolume(5.0f);
    menuMmusic.play();
    m_buttonClickSound.setBuffer(m_buttonClickBuffer);
    m_buttonClickSound.setVolume(200.0f);  // Set button click sound volume (adjust as needed)


    while (m_window->isOpen()) {
        if (handleInput() == START_GAME) break;
        show();
    }
}
