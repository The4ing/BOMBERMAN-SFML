#include "Board.h"


Board::Board()
    : m_rows(0), m_cols(0), m_FreezeGuardsStatus(false), m_lives(0) {
    m_robot = std::make_unique<Robot>();
    loadTextures();
    srand(static_cast<unsigned int>(time(0)));
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

    // Set scale factors for uniform scaling (adjust these values as needed)
   

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
                std::unique_ptr<Guard> guard;

                if (isGuardSmart(5)) {
                    guard = std::make_unique<SmartGuard>();  // Create a smart guard
                }
                else {
                    guard = std::make_unique<StupidGuard>();  // Create a stupid guard
                }

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

void Board::GenerateBomb()
{
    auto bomb = std::make_unique<Bomb>(GetTexture(BOMB));
    sf::Vector2f RobotPos = m_robot->getPosition();
    bomb->setPosition(RobotPos.x, RobotPos.y);
    m_movingObjects.push_back(std::move(bomb));
}


void Board::loadTextures() {
    m_textures.resize(TEXTURE_COUNT);
    const std::map<int, std::string> textureFiles = {
        {WALL, "wall.png"},
        {ROCK, "rock.png"},
        {GUARD, "guard.png"},
        {DOOR, "door.png"},
        {EMPTY, "empty.png"},
        {BOMB,"bomb.png"},
    };

    for (const auto& [index, filename] : textureFiles) {
        if (!m_textures[index].loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        }
    }
}

const sf::Texture& Board::GetTexture(const int choice) const {
    return m_textures[choice];
}



// Set the probability based on the level
// For example, level 1 = 10% chance, level 10 = 90% chance, and so on
bool Board::setSmartGuard(int level) {
    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));
    int probability = std::min(100, level * 10);  // Cap the probability at 100%

    // Generate a random number between 1 and 100
    int randomNumber = rand() % 100 + 1;

    // Return true if the random number is less than or equal to the probability
    return randomNumber <= probability;
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



void Board::callUpdateToolbar(const float deltatime) {
    m_Toolbar.callUpdateToolbar(deltatime);
}

void Board::draw(sf::RenderWindow& window) {
    m_Toolbar.draw(window);
}

const int Board::getHeartCount() {
    return m_Toolbar.getHeartCount();
}

//void Board::SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const {
//    picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
//    picture.setPosition(POSx, POSy);
//    picture.setScale(thicknes, thicknes);
//}





void Board::display(sf::RenderWindow& window) {
    // Draw the toolbar
    m_Toolbar.draw(window);

    // Draw static objects
    for (const auto& obj : m_objects) {
        obj->draw(window);
    }

    //// Remove bombs only if they are ready to be removed (after explosion display)
    //std::erase_if(m_movingObjects, [](const auto& obj) {
    //    auto bomb = dynamic_cast<Bomb*>(obj.get()); // Use smart pointers
    //    return bomb && bomb->CanBeRemoved();
    //    });

    // Draw remaining moving objects
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

//sf::Vector2f Board::getRobotScreenPosition(const sf::RenderWindow& window)   {
//    float frameWidth = window.getSize().x * 0.8f;
//    float frameHeight = window.getSize().y * 0.8f;
//    float cellWidth = frameWidth / m_cols;
//    float cellHeight = frameHeight / m_rows;
//
//    float offsetX = (window.getSize().x - frameWidth) / 2.0f;
//    float offsetY = (window.getSize().y - frameHeight) / 2.0f;
//
//    m_cellSize = { cellWidth, cellHeight };
//
//    sf::Vector2f RobotPos = m_robot->getPosition();
//    float screenX = RobotPos.x * cellWidth + offsetX;
//    float screenY = RobotPos.y * cellHeight + offsetY;
//
//    return {screenX, screenY };
//}






sf::Vector2f Board::getCellSize() const {
    return m_cellSize;
}

void Board::update(const float deltaTime) {
    // Update the robot's state
    m_robot->update(deltaTime);

    // Update the toolbar
    m_Toolbar.CallUpdateTimer();
    m_Toolbar.callUpdateToolbar(deltaTime);

    // Update moving objects and check for collisions
    for (auto& obj : m_movingObjects) {
        obj->update(deltaTime);

        // Check for collisions with static objects
        for (const auto& staticObj : m_objects) {
            if (obj->getGlobalBounds().intersects(staticObj->getGlobalBounds())) {
                obj->collideWith(staticObj.get());
            }
        }

        // Check for collisions with the robot
        if (obj->getGlobalBounds().intersects(m_robot->getGlobalBounds())) {
            obj->collideWith(m_robot.get());
        }
        
        if (m_robot->CheckHitByBOMB()) {
             //m_Toolbar
            m_robot->SetIfHitByBomb(false);
        }
        // Additional logic for smart guards
        checkIfSmartGuard(obj.get());
    }

    // Handle explosions and remove bombs
    std::erase_if(m_movingObjects, [this](const auto& movingObj) {
        if (auto* bomb = dynamic_cast<Bomb*>(movingObj.get()); bomb) {
            if (bomb->CheckBombExplode()) {
                // Process explosion effects
                sf::FloatRect explosionArea = bomb->getExplosionArea();

                // Remove guards and rocks in the explosion area
                std::erase_if(m_movingObjects, [&explosionArea](const auto& obj) {
                    auto* guard = dynamic_cast<Guard*>(obj.get());
                    return guard && guard->getGlobalBounds().intersects(explosionArea);
                    });
                std::erase_if(m_objects, [&explosionArea](const auto& obj) {
                    auto* rock = dynamic_cast<Rock*>(obj.get());
                    return rock && rock->getGlobalBounds().intersects(explosionArea);
                    });
            }
            return bomb->CanBeRemoved(); // Remove bomb only after explosion texture is shown
        }
        return false;
        });


    // Check for collisions between the robot and static objects
    for (const auto& staticObj : m_objects) {
        if (m_robot->getGlobalBounds().intersects(staticObj->getGlobalBounds())) {
            m_robot->collideWith(staticObj.get());
        }
    }
}


void Board::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (m_robot) {
        m_robot->handleInput(key, isPressed); // Forward input to the robot
    }
}

bool Board::isGuardSmart(int level) {
    // Generate a random number between 0 and 99
    int intelligence = rand() % 100;

    // Scale the probability based on the level
    int probability = std::min(100, level * 10);

    // Return true if the intelligence value falls within the probability range
    return intelligence < probability;
}



void Board::checkIfSmartGuard(MovingGameObject* obj) {
    if (auto* smartGuard = dynamic_cast<SmartGuard*>(obj)) {
        //std::cout << "This is a SmartGuard.\n";
        smartGuard->setPlayerPosition(m_robot->getPosition());
    }
    else {
        //std::cout << "This is not a SmartGuard.\n";
    }
}

void Board::handleMouseClick(sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition) {
    m_Toolbar.handleMouseClick(window, mousePixelPosition);
}
