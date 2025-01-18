#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "Board.h"
#include "Robot.h" // Include the Robot class

// Constructor
GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
    m_robotLives(3),
    m_pause(false),
    m_arrowKeyPressed(false),
    m_robotDirection(STAND), // Default robot direction
    m_mainMenu(&m_window, 0), // Initialize MainMenuDisplay with window and dummy game ID
    m_gameScreen(&m_window),  // Initialize GameDisplay with window
    m_settingsScreen(&m_window), // Initialize SettingsDisplay with window
    m_robot() // Initialize Robot
{
    m_board.loadFromFile("level1.txt");
    m_board.loadTextures();

    // Set the robot's initial position
    m_robot.setPosition(100.f, 100.f); // Adjust starting position as needed
}

void GameManager::newGame() {
    m_robotLives = 3;
    m_pause = false;
    m_board.loadFromFile("level1.txt"); // Reload the level
    m_robot.setPosition(100.f, 100.f); // Reset robot's position
    std::cout << "New game started!" << std::endl;

    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN",
        sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    m_mainMenu.Run();
    startGame();
}







void GameManager::startGame() {
    sf::Clock clock;

    // Set the level duration in the Board (e.g., 180 seconds = 3 minutes)
    m_board.setTimer(40);  // 40 seconds for demonstration

    // Create an SFML text object for displaying the timer
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error: Failed to load font!" << std::endl;
        return;
    }

    sf::Text timerText;
    timerText.setFont(font);
    timerText.setCharacterSize(40);  // Set the font size
    timerText.setFillColor(sf::Color::Green);  // Initial color
    timerText.setPosition(10.f, 10.f);  // Set position on screen



    // Create a progress bar for the timer
    sf::RectangleShape progressBar(sf::Vector2f(200.f, 10.f));  // Width is based on time remaining
    progressBar.setFillColor(sf::Color::Green);
    progressBar.setPosition(10.f, 70.f);  // Positioning below the timer text

    
    // Create the clock hand sprite
    sf::Sprite clockHand(m_board.GetTexture(CLOCK));
    m_board.SetSprite(clockHand, 400.f, 50.f, 0.2f);  // Center the clock on the screen

    // Create the arrow sprite
    sf::Sprite arrow(m_board.GetTexture(ARROW));
    m_board.SetSprite(arrow, clockHand.getPosition().x, clockHand.getPosition().y, 0.4f);  // Center the clock on the screen
    

    // Assuming you want an array of 3 sprites, each with a decreasing position
    std::vector<sf::Sprite> heart;  // Create a single vector to store all sprites
    heart.reserve(NUM_HEART);  // Reserve space for 3 sprites

    int decrease = 1800;
    for (int i = 0; i < NUM_HEART; ++i) {
        sf::Sprite picture;  // Create a sprite
        picture.setTexture(m_board.GetTexture(HEART));  // Assign texture to sprite
        m_board.SetSprite(picture, decrease, 50.f, 0.2f);  // Set position and scale
        heart.push_back(picture);  // Add the sprite to the vector
        decrease -= 200;  // Decrease the position for the next sprite
    }

    
     


    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();  // Calculate deltaTime each frame
        float deltaTimeInSeconds = deltaTime.asSeconds();

        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
                m_robot.handleInput(event.key.code, event.type == sf::Event::KeyPressed);
            }
        }

        // Update robot and other game elements
        m_robot.update(deltaTimeInSeconds);

        // Update the timer display and progress bar (including clock hand rotation)
        m_board.updateTimerDisplay(timerText, progressBar, arrow, heart, deltaTimeInSeconds);


        // Render the game
        m_window.clear();
        m_board.display(m_window);  // Draw the board
        m_robot.draw(m_window);     // Draw the robot


        // Loop through all the heart sprites and draw them
        for (int pos = 0; pos < heart.size(); pos++) {
            m_window.draw(heart[pos]);  // Draw each heart sprite
        }

        

        // Draw the clock hand (robot image) here
        m_window.draw(clockHand);  // Draw the clock hand sprite
        m_window.draw(arrow);  // Draw the arrow hand sprite

       

        // Draw the timer and progress bar
        m_window.draw(progressBar);  // Draw the progress bar
        m_window.draw(timerText);    // Draw the timer text

        m_window.display();
    }
}






bool GameManager::loadLevel(const std::string& fileName) {
    //return m_board.loadFromFile(fileName); // Update this if level loading requires specific logic
    return true;
}

void GameManager::processGameEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Escape) {
                m_robotLives = 3;
                m_mainMenu.Run();
                return;
            }
            if (event.key.code == sf::Keyboard::X) {
                std::cout << "Bomb dropped!\n"; // Logic for dropping a bomb
            }
            else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
                event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                handleMoveKeys(event.key.code, true);
            }
        } break;

        case sf::Event::KeyReleased: {
            if (event.key.code == sf::Keyboard::X)
                break;

            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down ||
                event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                handleMoveKeys(event.key.code, false);
            }
        } break;

        default:
            break;
        }
    }
}

void GameManager::handleMoveKeys(sf::Keyboard::Key key, const bool isPressed) {
    if (!m_pause) {
        // Delegate movement input to the Robot class
        m_robot.handleInput(key, isPressed);
        m_arrowKeyPressed = isPressed;
    }
}
