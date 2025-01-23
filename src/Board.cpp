#include "Board.h"


Board::Board()
    : m_rows(0), m_cols(0), m_FreezeGuardsStatus(false), m_lives(0) {
    m_robot = std::make_unique<Robot>();
    loadTextures();
}


void Board::loadFromFile(const std::string& fileName) {
    isGuardSmart(1);
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    m_rows = lines.size();
    m_cols = lines.empty() ? 0 : lines[0].size();

    // Calculate cell size considering the toolbar
    float windowWidth = 1920.0f; // Example window width
    float windowHeight = 1080.0f; // Example window height
    float gridHeight = windowHeight - TOOLBAR_HEIGHT; // Remaining height after the toolbar

    m_cellSize.x = windowWidth / static_cast<float>(m_cols);
    m_cellSize.y = gridHeight / static_cast<float>(m_rows);

    int guardCount = 0;

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            sf::Vector2f position(j * m_cellSize.x, i * m_cellSize.y + TOOLBAR_HEIGHT); // Offset by toolbar height
            switch (symbol) {
            case '#': {
                auto wall = std::make_unique<Wall>(GetTexture(WALL));
                wall->setPosition(position.x, position.y);
                m_objects.push_back(std::move(wall));
                break;
            }
            case '/':
                m_robot->setPosition(position.x, position.y);
                break;
            case '!': {
                // Add guard (example: StupidGuard)
                auto guard = std::make_unique<StupidGuard>();
                guard->setPosition(position.x, position.y);
                m_movingObjects.push_back(std::move(guard));
                guardCount++;
                break;
            }
            case '@': {
                auto rock = std::make_unique<Rock>(GetTexture(ROCK));
                rock->setPosition(position.x, position.y);
                m_objects.push_back(std::move(rock));
                break;
            }
            case 'D': {
                auto door = std::make_unique<Door>(GetTexture(DOOR));
                door->setPosition(position.x, position.y);
                m_objects.push_back(std::move(door));
                break;
            }
            default:
                break;
            }
        }
    }

    std::cout << "Number of guards created: " << guardCount << std::endl;

}



void Board::PowerUp(const powerUps choice) {
    switch (choice) {
    case FreezeGuards:
       // FreezeAllGuards(true);
        std::cout << "All guards have been frozen!" << std::endl;
        break;
    case ExtraLife:
        GrantExtraLife();
        std::cout << "An extra life has been granted!" << std::endl;
        break;
    case RemovedGuard:
        // Implement logic to remove a guard
        std::cout << "A guard has been removed!" << std::endl;
        break;
    case TimeIncrease:
        m_Toolbar.IncreaseTime(30);
        std::cout << "Time has been increased!" << std::endl;
        break;
    default:
        std::cout << "Invalid power-up choice!" << std::endl;
        break;
    }
}

//void Board::FreezeAllGuards(const bool status) {
//    m_FreezeGuardsStatus = status;
//    for (const auto& obj : m_movingObjects) {
//        if (auto guard = dynamic_cast<Guard*>(obj.get())) {
//            guard->setFrozen(status);
//        }
//    }
//}

void Board::GrantExtraLife() {
    m_lives++;
}

const sf::Texture& Board::GetTexture(const int choice) const {
    return m_textures[choice];
}

void Board::callUpdateToolbar(const float deltatime) {
    m_Toolbar.callUpdateToolbar(deltatime);
}

void Board::draw(sf::RenderWindow& window) {
    m_Toolbar.draw(window);
}

const int Board::getHeartCount() {
    return m_Toolbar.getHeartCount();
}

void Board::SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const {
    picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
    picture.setPosition(POSx, POSy);
    picture.setScale(thicknes, thicknes);
}



void Board::loadTextures() {
    m_textures.resize(TEXTURE_COUNT);
    const std::map<int, std::string> textureFiles = {
        {WALL, "wall.png"},
        {ROCK, "rock.png"},
        {GUARD, "guard.png"},
        {DOOR, "door.png"},
        {EMPTY, "empty.png"},
    };

    for (const auto& [index, filename] : textureFiles) {
        if (!m_textures[index].loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        }
    }
}

void Board::display(sf::RenderWindow& window)  {
    // Draw the toolbar
    m_Toolbar.draw(window);

    // Draw static objects
    for (const auto& obj : m_objects) {
        obj->draw(window);
    }

    // Draw moving objects
    for (const auto& obj : m_movingObjects) {
        obj->draw(window);
    }

    // Draw the robot separately
    if (m_robot) {
        m_robot->draw(window);
    }
    else {
        std::cerr << "Error: Robot object is null." << std::endl;
    }
}





void Board::displayConsole() const {
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            bool found = false;

            for (const auto& obj : m_objects) {
                if (obj->getPosition().x == j && obj->getPosition().y == i) {
                    std::cout << obj->getSymbol();
                    found = true;
                    break;
                }
            }

            if (!found) {
                for (const auto& obj : m_movingObjects) {
                    if (obj->getPosition().x == j && obj->getPosition().y == i) {
                        std::cout << obj->getSymbol();
                        found = true;
                        break;
                    }
                }
            }

            if (!found) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

sf::Vector2f Board::getRobotScreenPosition(const sf::RenderWindow& window)   {
    float frameWidth = window.getSize().x * 0.8f;
    float frameHeight = window.getSize().y * 0.8f;
    float cellWidth = frameWidth / m_cols;
    float cellHeight = frameHeight / m_rows;

    float offsetX = (window.getSize().x - frameWidth) / 2.0f;
    float offsetY = (window.getSize().y - frameHeight) / 2.0f;

    m_cellSize = { cellWidth, cellHeight };

    sf::Vector2f RobotPos = m_robot->getPosition();
    float screenX = RobotPos.x * cellWidth + offsetX;
    float screenY = RobotPos.y * cellHeight + offsetY;

    return {screenX, screenY };
}


sf::Vector2f Board::getCellSize() const {
    return m_cellSize;
}

void Board::update(float deltaTime) {
    // Calculate board boundaries
    float leftBound = 0.f;
    float topBound = TOOLBAR_HEIGHT; // Offset for toolbar
    float rightBound = m_cols * (m_cellSize.x + 1);
    float bottomBound = TOOLBAR_HEIGHT + m_rows * m_cellSize.y;

    m_Toolbar.CallUpdateTimer();
    m_Toolbar.callUpdateToolbar(deltaTime);
    // Update moving objects like guards
    for (auto& obj : m_movingObjects) {
        obj->update(deltaTime);
        sf::Vector2f objectPos = obj->getPosition();
        if (objectPos.x < leftBound) {
			objectPos.x = leftBound;
        }
        else if (objectPos.x + m_cellSize.x > rightBound) {
            objectPos.x = rightBound - m_cellSize.x;
        }

        if (objectPos.y < topBound) {
            objectPos.y = topBound;
        }
        else if (objectPos.y + m_cellSize.y > bottomBound) {
            objectPos.y = bottomBound - m_cellSize.y;
        }

        // Apply corrected position
        obj->setPosition(objectPos.x, objectPos.y);
    }

    // Update robot position and animation
    m_robot->update(deltaTime);

    // Boundary checks for the robot
    sf::Vector2f robotPos = m_robot->getPosition();


    // Ensure the robot stays within bounds
    if (robotPos.x < leftBound) {
        robotPos.x = leftBound;
    } else if (robotPos.x + m_cellSize.x > rightBound) {
        robotPos.x = rightBound - m_cellSize.x;
    }

    if (robotPos.y < topBound) {
        robotPos.y = topBound;
    } else if (robotPos.y + m_cellSize.y > bottomBound) {
        robotPos.y = bottomBound - m_cellSize.y;
    }

    // Apply corrected position
    m_robot->setPosition(robotPos.x, robotPos.y);
}


void Board::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (m_robot) {
        m_robot->handleInput(key, isPressed); // Forward input to the robot
    }
}

bool Board::isGuardSmart(int level)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int intelligence = rand() % (level + 5);
    std::cout << intelligence << std::endl;
    if (intelligence < 1) {
        intelligence = 1;
    }
    return true;
}