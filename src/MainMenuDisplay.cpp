#include "MainMenuDisplay.h"
#include <iostream>

// Constructor
MainMenuDisplay::MainMenuDisplay(sf::RenderWindow* window, int game)
    : m_window(window), m_game(game), m_state(MAIN_MENU) {
    // Load main menu background
    if (!m_mainBackgroundTexture.loadFromFile("menu.png")) {
        std::cerr << "Error loading main menu background!" << std::endl;
    }
    m_mainBackgroundSprite.setTexture(m_mainBackgroundTexture);

    // Load help menu background
    if (!m_helpBackgroundTexture.loadFromFile("helpBackground.png")) {
        std::cerr << "Error loading help menu background!" << std::endl;
    }
    m_helpBackgroundSprite.setTexture(m_helpBackgroundTexture);

    // Load font
    if (!m_font.loadFromFile("PixelFontBlack.otf")) {
        std::cerr << "Error loading font!" << std::endl;
    }

    // Load and play background music
    if (!m_menuMusic.openFromFile("menuMusic.ogg")) {
        std::cerr << "Error loading menu music!" << std::endl;
    }
    m_menuMusic.setLoop(true); // Loop the music
    m_menuMusic.setVolume(20);
    m_menuMusic.play();        // Start playing the music


    // Load button sound
    if (!m_buttonClickBuffer.loadFromFile("ButtonMusic.ogg")) {
        std::cerr << "Error loading button click sound!" << std::endl;
    }
    m_buttonClickSound.setBuffer(m_buttonClickBuffer);



    // Configure buttons
    configureButton(m_startButton, "Start Game", sf::Color::Black, -100);
    configureButton(m_helpButton, "Help", sf::Color::Black, 0);
    configureButton(m_exitButton, "Exit", sf::Color::Black, 100);

    // Configure hover text
    m_hoverExplanationText.setFont(m_font);
    m_hoverExplanationText.setCharacterSize(24);
    m_hoverExplanationText.setFillColor(sf::Color::Red);

    // Configure instruction text
    m_instructionText.setFont(m_font);
    m_instructionText.setString("Hover over the pictures to see explanations.");
    m_instructionText.setCharacterSize(24);
    m_instructionText.setFillColor(sf::Color::White);
    m_instructionText.setPosition(20, 20);



    // Load and initialize help objects
    initializeHelpObjects();



    // Load button sound
    m_ButtonXPL.resize(1);

    if (!m_ButtonXPL[0].loadFromFile("RobotXPL.ogg")) {
        std::cerr << "Error loading button click sound!" << std::endl;
    }


}

// Configure buttons
void MainMenuDisplay::configureButton(sf::Text& button, const std::string& label, const sf::Color& color, int yOffset) {
    float windowWidth = m_window->getSize().x;
    float windowHeight = m_window->getSize().y;

    button.setFont(m_font);
    button.setString(label);
    button.setCharacterSize(40);
    button.setFillColor(color);

    sf::FloatRect bounds = button.getLocalBounds();
    button.setOrigin(bounds.width / 2, bounds.height / 2);
    button.setPosition(windowWidth / 2, (windowHeight / 2) + yOffset);
}

// Initialize help objects
void MainMenuDisplay::initializeHelpObjects() {
    const std::vector<std::string> textureFiles = {
        "wall.png", "Robot.png", "Bomb.png", "Guard.png", "Door.png", "Rock.png"
    };
    const std::vector<std::string> explanations = {
        "Wall: An obstacle.",
        "Robot: The main character which needs to escape through the door!",
        "Bomb: Handle with care.",
        "Guard: Be cautious!",
        "Door: Leads to the next area.",
        "Rock: A simple barrier."
    };

    float windowWidth = m_window->getSize().x;
    float windowHeight = m_window->getSize().y;

    float desiredWidth = windowWidth * 0.1f;
    float desiredHeight = windowHeight * 0.1f;

    for (size_t i = 0; i < textureFiles.size(); ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFiles[i])) {
            std::cerr << "Error loading texture: " << textureFiles[i] << std::endl;
            continue;
        }
        m_helpTextures.push_back(texture);

        sf::Sprite sprite(m_helpTextures.back());
        sf::Vector2u textureSize = texture.getSize();
        sprite.setScale(desiredWidth / textureSize.x, desiredHeight / textureSize.y);

        float x = windowWidth * (0.15f + (i % 3) * 0.3f);
        float y = windowHeight * (0.3f + (i / 3) * 0.3f);
        sprite.setPosition(x, y);

        m_helpSprites.push_back(sprite);
        m_helpExplanations.push_back(explanations[i]);
    }
}

// Handle user input
int MainMenuDisplay::handleInput() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && m_state == HELP_SCREEN) {
            m_state = MAIN_MENU;
        }

        if (event.type == sf::Event::MouseMoved) {
            handleHover(sf::Mouse::getPosition(*m_window));
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (handleButtonClick(sf::Mouse::getPosition(*m_window)) == START_GAME) {
                return START_GAME;
            }
        }
    }
    return 0;
}

// Handle hover effects
void MainMenuDisplay::handleHover(const sf::Vector2i mousePosition) {
    sf::Vector2f worldMousePos = m_window->mapPixelToCoords(mousePosition);
    if (m_state == MAIN_MENU) {
        auto setHoverEffect = [&](sf::Text& button) {
            if (button.getGlobalBounds().contains(worldMousePos)) {
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
    else if (m_state == HELP_SCREEN) {
        bool hovered = false;


        for (size_t i = 0; i < m_helpSprites.size(); ++i) {
            if (m_helpSprites[i].getGlobalBounds().contains(worldMousePos)) {
                //for button
                if (i == 1 && !played) {
                    ButtonSounds.setBuffer(m_ButtonXPL[0]);
                    ButtonSounds.play(); // Sound will now play because the object persists
                    played = true;
                }
                //

                m_hoverExplanationText.setString(m_helpExplanations[i]);
                m_hoverExplanationText.setPosition(worldMousePos.x + 15, worldMousePos.y + 15);
                hovered = true;
                break;
            }
        }
        if (!hovered) {
            //added for the button
            played = false;
            ButtonSounds.stop();
            //
            m_hoverExplanationText.setString("");
        }
    }
}

// Show menu or help screen
void MainMenuDisplay::show() {
    m_window->clear();

    if (m_state == MAIN_MENU) {
        m_window->draw(m_mainBackgroundSprite);
        m_window->draw(m_startButton);
        m_window->draw(m_helpButton);
        m_window->draw(m_exitButton);
    }
    else if (m_state == HELP_SCREEN) {
        m_window->draw(m_helpBackgroundSprite);
        m_window->draw(m_instructionText);
        for (const auto& sprite : m_helpSprites) {
            m_window->draw(sprite);
        }
        m_window->draw(m_hoverExplanationText);
    }

    m_window->display();
}

// Handle button clicks
int MainMenuDisplay::handleButtonClick(const sf::Vector2i mousePosition) {
    sf::Vector2f worldMousePos = m_window->mapPixelToCoords(mousePosition);

    if (m_startButton.getGlobalBounds().contains(worldMousePos)) {
        m_buttonClickSound.play();
        return START_GAME;
    }
    if (m_helpButton.getGlobalBounds().contains(worldMousePos)) {
        m_buttonClickSound.play();
        m_state = HELP_SCREEN;
    }
    if (m_exitButton.getGlobalBounds().contains(worldMousePos)) {
        m_buttonClickSound.play();
        m_window->close();
    }
    return 0;
}

// Run the menu loop
void MainMenuDisplay::Run() {
    while (m_window->isOpen()) {
        if (handleInput() == START_GAME) break;
        show();
    }
}
