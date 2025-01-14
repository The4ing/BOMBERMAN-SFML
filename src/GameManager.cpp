#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>

GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
    m_mainMenu(&m_window, 0),
    m_gameScreen(&m_window),
    m_settingsScreen(&m_window),
    m_board()
{


    //for timer
    if (!m_font.loadFromFile("PixelFontBlack.otf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
    m_timerText.setFont(m_font);
    m_timerText.setCharacterSize(24);  // Adjust size as needed
    m_timerText.setFillColor(sf::Color::Red);
    m_timerText.setPosition(10, 10);  // Set position on the screen
}


void GameManager::startGame() {
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN", sf::Style::Titlebar | sf::Style::Close);

    //for timer
    m_board.setLevelDuration(300.0f);  // Set level duration to 5 minutes, for example


    while (m_window.isOpen()) {

        //for timer
          m_board.UpdateTimer();  // Update the board timer
         // Update the timer text
         m_timerText.setString("Time: " + m_board.getTimeString());


         m_mainMenu.Run();
         // Update game logic
       
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();
        }

        

        // Render everything
         render();
        
    }
}




bool GameManager::loadLevel(const std::string& fileName) {
    return true;
}


//add
void GameManager::render() {
    m_window.clear();

    // Draw timer
    m_window.draw(m_timerText);

    // Add other rendering logic here (e.g., game objects)

    m_window.display();
}
