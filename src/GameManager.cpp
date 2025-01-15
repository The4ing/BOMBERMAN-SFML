#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <SFML/Audio.hpp>
#include "Board.h"

GameManager::GameManager()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN"),
	m_robotLives(3),
	m_pause(false),
    m_mainMenu(&m_window, 0),             // Initialize MainMenuDisplay with window and dummy game ID
    m_gameScreen(&m_window),              // Initialize GameDisplay with window
    m_settingsScreen(&m_window)           // Initialize SettingsDisplay with window

{
    m_board.loadFromFile("level1.txt");
    m_board.loadTextures();
}

void GameManager::newGame()
{
    m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BOMBERMAN", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    m_mainMenu.Run();
    startGame();
}


void GameManager::startGame() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                m_window.close();

            if (event.type == sf::Event::Resized) {
                // Adjust the view when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                m_window.setView(sf::View(visibleArea));
            }
            if (event.key.code == sf::Keyboard::Escape) {
                m_mainMenu.Run();
            }
        }

        m_window.clear();
        m_board.display(m_window);
        m_window.display();
    }
}


bool GameManager::loadLevel(const std::string& fileName) {
    return true;
}

void GameManager::processGameEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: m_window.close(); break;
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) {
				m_robotLives = 3;
				m_mainMenu.Run();
				return;
			}
			if (event.key.code == sf::Keyboard::X)std::cout << "bomb displayes\n";//m_robot->dropBomb();
			else if (event.key.code == sf::Keyboard::Up
				|| event.key.code == sf::Keyboard::Down
				|| event.key.code == sf::Keyboard::Right
				|| event.key.code == sf::Keyboard::Left)
				handleMoveKeys(event.key.code, true);
		}
		break;
		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::X) break;
			if (event.key.code == sf::Keyboard::Space) {
				/*if (m_timer.isRunning()) { //logic to space pressed
					ResourceManager::getResource().pauseSound("music");
					for (auto& enemy : m_enemies) {
						enemy->stopAnimation();
					}
					m_timer.stop();
					m_pause = true;
					m_robotDirection = STAND;
				}
				else {
					ResourceManager::getResource().playSound("music");
					m_timer.start();
					m_pause = false;
				}
				break;*/
			}
			if (event.key.code == sf::Keyboard::Up
				|| event.key.code == sf::Keyboard::Down
				|| event.key.code == sf::Keyboard::Right
				|| event.key.code == sf::Keyboard::Left)
				handleMoveKeys(event.key.code, false);
			//m_updateAnimation = true;
			//m_robot->playAnimation(STAND);
			break;
		default:;
		}
	}
}


void GameManager::handleMoveKeys(sf::Keyboard::Key key, const bool isPressed)
{
    if (!m_pause) {
        switch (key) {
        case sf::Keyboard::Up: m_robotDirection = UP; break;
        case sf::Keyboard::Down: m_robotDirection = DOWN; break;
        case sf::Keyboard::Right: m_robotDirection = RIGHT; break;
        case sf::Keyboard::Left: m_robotDirection = LEFT; break;
        default:;
        }
        m_arrowKeyPressed = isPressed;
    }
}
