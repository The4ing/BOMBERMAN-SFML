#include "MainMenuDisplay.h"

MainMenuDisplay::MainMenuDisplay(sf::RenderWindow* window, int game)
    : m_window(window), m_game(game), m_state(MAIN_MENU), played(false){
    ResourceManager& resourceManager = ResourceManager::getInstance();
    m_mainBackgroundSprite.setTexture(resourceManager.getTexture("menu.png"));
    m_helpBackgroundSprite.setTexture(resourceManager.getTexture("helpBackground.png"));
    m_helpBackgroundSprite.setColor(sf::Color(150, 150, 150, 255));  // Reduce RGB values to darken
    m_esc.setTexture(resourceManager.getTexture("ESC.png"));
    float scaleFactor = 0.6f;
    m_esc.setScale(scaleFactor, scaleFactor);
    float windowWidth = m_window->getSize().x;
    sf::Vector2u textureSize = m_esc.getTexture()->getSize();
    float scaledWidth = textureSize.x * scaleFactor;
    float scaledHeight = textureSize.y * scaleFactor;
    float margin = 20.0f;
    m_esc.setPosition(windowWidth - scaledWidth - margin, margin + 200.0f);
    sf::Music& BGMusic = resourceManager.getMusic("menuMusic");
    BGMusic.setLoop(false);
    BGMusic.setVolume(20);
    BGMusic.play();
    played.resize(NUM_XPL);
    
    configureButton("Start Game", sf::Color::Black, -100);
    configureButton("Help", sf::Color::Black, 0);
    configureButton("Exit", sf::Color::Black, 100);

    sf::Text hoverExplanationText;
    std::string fontFile = "PixelFontBlack.otf";
    hoverExplanationText.setFont(resourceManager.getFont(fontFile));
    hoverExplanationText.setCharacterSize(24);
    hoverExplanationText.setFillColor(sf::Color(255, 165, 0));
    resourceManager.addText(fontFile, hoverExplanationText);

    m_instructionText.setFont(resourceManager.getFont("PixelFontBlack.otf"));
    m_instructionText.setString("Hover over the pictures to see explanations.");
    m_instructionText.setCharacterSize(30);
    m_instructionText.setFillColor(sf::Color(144, 238, 144));
    m_instructionText.setPosition(20, 20);

    m_AboutGame.setFont(resourceManager.getFont("PixelFontBlack.otf"));
    m_AboutGame.setString(resourceManager.getString("AboutGame"));
    m_AboutGame.setCharacterSize(25);
    m_AboutGame.setFillColor(sf::Color(0, 255, 0));
    m_AboutGame.setPosition(20, 65); 
    sf::FloatRect textBounds = m_AboutGame.getGlobalBounds();

    sf::RectangleShape aboutBackground;
    aboutBackground.setSize(sf::Vector2f(textBounds.width + 20, textBounds.height + 20)); 
    aboutBackground.setPosition(textBounds.left - 10, textBounds.top - 10);  
    aboutBackground.setFillColor(sf::Color(0, 0, 0, 100));  
    m_rectangles.push_back(aboutBackground);
   
    m_ButtonsXPL = {
         "WallXPL","RobotXPL","BombXPL","SmartGuardXPL",
         "DoorXPL", "RockXPL","StupidGuardXPL","PresentXPL"
    };

    initializeHelpObjects();
}

void MainMenuDisplay::configureButton(const std::string& label, const sf::Color& color, int yOffset) {
    sf::Text button;
    ResourceManager& resourceManager = ResourceManager::getInstance();
    button.setFont(resourceManager.getFont("PixelFontBlack.otf"));
    button.setString(label);
    button.setCharacterSize(40);
    button.setFillColor(color);

    float window_width = m_window->getSize().x;
    float window_height = m_window->getSize().y;

    sf::FloatRect bounds = button.getLocalBounds();
    button.setOrigin(bounds.width / 2, bounds.height / 2);
    button.setPosition(window_width / 2, (window_height / 2) + yOffset);

    resourceManager.addText(label, button);

    // --- Create the Frame Sprite ---
    sf::Sprite frameSprite;
    frameSprite.setTexture(resourceManager.getTexture("button_frame.png")); // Load the frame texture

    // Scale the frame to fit the text size
    sf::Vector2u frameSize = frameSprite.getTexture()->getSize();
    float scaleX = (bounds.width + 40) / (frameSize.x - 10);  // Add padding to width
    float scaleY = (bounds.height + 20) / (frameSize.y - 10); // Add padding to height
    frameSprite.setScale(scaleX, scaleY);

    // Position the frame to align with the text
    frameSprite.setPosition(button.getPosition().x - (bounds.width / 2) - 20,
        button.getPosition().y - (bounds.height / 2));

    m_buttonFrames[label] = frameSprite;  // Store frame
}

void MainMenuDisplay::initializeHelpObjects() {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    const std::vector<std::string> textureFiles = {
        "wall.png", "Robot.png", "bomb.png", "rick_guard.png", "door.png",
        "rock.png", "guard_morty.png" ,"present.png"
    };
    
    float desiredWidth = WINDOW_WIDTH * 0.1f;
    float desiredHeight = WINDOW_HEIGHT * 0.1f;
    float margin = 0.05f * WINDOW_WIDTH;     

    for (size_t i = 0; i < textureFiles.size(); ++i) {
      
        if (resourceManager.getTexture(textureFiles[i]).getSize().x == 0) {
            std::cerr << "Error: Texture not found: " << textureFiles[i] << std::endl;
            continue; 
        }

        sf::Sprite sprite;
        sprite.setTexture(resourceManager.getTexture(textureFiles[i]));

        sf::Vector2u textureSize = resourceManager.getTexture(textureFiles[i]).getSize();
        sprite.setScale(desiredWidth / textureSize.x, desiredHeight / textureSize.y);

        float x = margin + (i % 3) * (WINDOW_WIDTH * 0.28f);  // 3 columns, horizontal distribution
        float y = WINDOW_HEIGHT * (0.25f + (i / 3) * 0.25f);  // Reduced the starting y value to move sprites higher

        sprite.setPosition(x, y);

        sf::RectangleShape outline(sf::Vector2f(desiredWidth, desiredHeight));
        outline.setPosition(x, y);
        outline.setFillColor(sf::Color::Transparent);  // No fill, just an outline
        outline.setOutlineThickness(4);  // Thickness of the border
        outline.setOutlineColor(sf::Color::White);  // White outline
       
        m_rectangles.push_back(outline);  // Store the rectangle
        m_helpSprites.push_back(sprite);
        m_helpExplanations.push_back(resourceManager.getString(m_ButtonsXPL[i]));

    }
}

int MainMenuDisplay::handleInput() {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    sf::Music& BGMusic = resourceManager.getMusic("menuMusic");

    sf::Event event;
    while (m_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window->close();
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && m_state == HELP_SCREEN) {
            m_state = MAIN_MENU;
            for (auto& soundBuf : m_ButtonsXPL) {
                sf::Sound& explosionSound = resourceManager.getSound(soundBuf);
                explosionSound.stop();
            }
            std::fill(played.begin(), played.end(), false);  
        }

        if (event.type == sf::Event::MouseMoved) {
            handleHover(sf::Mouse::getPosition(*m_window));
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (handleButtonClick(sf::Mouse::getPosition(*m_window)) == START_GAME) {
                BGMusic.stop();
                return START_GAME;
            }
        }
    }
    return 0;
}

void MainMenuDisplay::handleHover(const sf::Vector2i mousePosition) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
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
        setHoverEffect(resourceManager.getText("Start Game"));
        setHoverEffect(resourceManager.getText("Help"));
        setHoverEffect(resourceManager.getText("Exit"));
    }
    else if (m_state == HELP_SCREEN) {
        bool hovered = false;

        for (size_t i = 0; i < m_helpSprites.size(); ++i) {
            if (m_helpSprites[i].getGlobalBounds().contains(worldMousePos)) {
                if (!played[i]) {
                    sf::Sound& explosionSound = resourceManager.getSound(m_ButtonsXPL[i]);
                    explosionSound.setVolume(50);
                    explosionSound.play();
                    played[i] = true;
                }

                // Set the help explanation text
                sf::Text& helpText = resourceManager.getText("PixelFontBlack.otf");
                helpText.setString(m_helpExplanations[i]);

                // Calculate text bounds to ensure it fits within the window
                sf::FloatRect textBounds = helpText.getGlobalBounds();
                float textWidth = textBounds.width;
                float textHeight = textBounds.height;

                // Adjust text position if it's going out of bounds
                float newPosX = worldMousePos.x + 15;
                float newPosY = worldMousePos.y + 15;

                // Ensure text doesn't go out of the right side of the window
                if (newPosX + textWidth > WINDOW_WIDTH) {
                    newPosX = WINDOW_WIDTH - textWidth - 15;  // Shift to the left
                }

                // Ensure text doesn't go out of the bottom side of the window
                if (newPosY + textHeight > WINDOW_HEIGHT) {
                    newPosY = WINDOW_HEIGHT - textHeight - 15;  // Shift upwards
                }

                helpText.setPosition(newPosX, newPosY);
               
                m_textBackground.setSize(sf::Vector2f(textWidth + 20, textHeight + 20));  // Padding around text
                m_textBackground.setPosition(newPosX - 10, newPosY - 10);  // Align with text
                m_textBackground.setFillColor(sf::Color(0, 0, 0, 255));
                hovered = true;
                break;
            }
        }

        if (!hovered) {
            // Stop sounds and clear text when not hovering
            for (auto& soundBuf : m_ButtonsXPL) {
                sf::Sound& explosionSound = resourceManager.getSound(soundBuf);
                explosionSound.stop();
            }
            std::fill(played.begin(), played.end(), false);  // Reset all elements to false

            resourceManager.getText("PixelFontBlack.otf").setString("");  // Clear the text

            m_textBackground.setSize(sf::Vector2f(0, 0));
        }
    }
}

void MainMenuDisplay::show() {
    m_window->clear();
    ResourceManager& resourceManager = ResourceManager::getInstance();

    if (m_state == MAIN_MENU) {
        m_window->draw(m_mainBackgroundSprite);

        // Draw Frames & Buttons
        for (const auto& pair : m_buttonFrames) {
            m_window->draw(pair.second);  // Draw frame
            m_window->draw(resourceManager.getText(pair.first)); // Draw button text
        }
    }
    else if (m_state == HELP_SCREEN) {
        m_window->draw(m_helpBackgroundSprite);
        m_window->draw(m_esc);
        m_window->draw(m_instructionText);
        for (const auto& rect : m_rectangles) {
            m_window->draw(rect);
        }
        for (const auto& sprite : m_helpSprites) {
            m_window->draw(sprite);
        }
        m_window->draw(m_AboutGame);
        m_window->draw(m_textBackground);
        m_window->draw(resourceManager.getText("PixelFontBlack.otf"));
    }

    m_window->display();
}

int MainMenuDisplay::handleButtonClick(const sf::Vector2i mousePosition) {
    if (m_state != MAIN_MENU) {
        return 0;
    }    
    sf::Vector2f worldMousePos = m_window->mapPixelToCoords(mousePosition);

    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sound& explosionSound = resourceManager.getSound("ButtonMusic");

    if (resourceManager.getText("Start Game").getGlobalBounds().contains(worldMousePos)) {
        explosionSound.setVolume(100);
        explosionSound.play();
        return START_GAME;
    }
    if (resourceManager.getText("Help").getGlobalBounds().contains(worldMousePos)) {
        explosionSound.setVolume(100);
        explosionSound.play();
        m_state = HELP_SCREEN;
    }
    if (resourceManager.getText("Exit").getGlobalBounds().contains(worldMousePos)) {
        explosionSound.setVolume(100);
        explosionSound.play();
        m_window->close();
    }
    return 0;
}

void MainMenuDisplay::Run() {
    while (m_window->isOpen()) {
        if (handleInput() == START_GAME) break;
        show();
    }
}
