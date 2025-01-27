#include "Board.h"


Board::Board()
    : m_rows(0), m_cols(0), m_FreezeGuardsStatus(false), m_lives(0) {
    m_robot = std::make_unique<Robot>();
    loadTextures();
    srand(static_cast<unsigned int>(time(0)));
}


void Board::loadFromFile(const std::string& fileName) {
    isGuardSmart(5);
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

    float gridHeight = WINDOW_HEIGHT - TOOLBAR_HEIGHT; // Remaining height after the toolbar

    m_cellSize.x = WINDOW_WIDTH / static_cast<float>(m_cols);
    m_cellSize.y = gridHeight / static_cast<float>(m_rows);
    float scaleX = m_cellSize.x / SINGLE_SPRITE_DIMENSIONS;
    float scaleY = m_cellSize.y / SINGLE_SPRITE_DIMENSIONS;
    int guardCount = 0;

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            sf::Vector2f position(j * m_cellSize.x, i * m_cellSize.y + TOOLBAR_HEIGHT); // Offset by toolbar height
            switch (symbol) {
            case '#': {
                auto wall = std::make_unique<Wall>(GetTexture(WALL));
                wall->setPosition(position.x, position.y);
                wall->setScale(scaleX, scaleY); // Ensure consistent scaling
                m_objects.push_back(std::move(wall));
                break;
            }
            case '/':
                m_robot->setPosition(position.x, position.y);
                std::cout << "Robot initial position: (" << position.x << ", " << position.y << ")\n";
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
                // Scale guards based on individual frame dimensions
                float guardScaleX = m_cellSize.x / 127.5f;  // 127.5 = guard frame width
                float guardScaleY = m_cellSize.y / 163.33f; // 163.33 = guard frame height
                guard->setScale(guardScaleX, guardScaleY);
                m_movingObjects.push_back(std::move(guard));
                guardCount++;
                break;
            }


            case '@': {
                auto rock = std::make_unique<Rock>(GetTexture(ROCK));
                rock->setPosition(position.x, position.y);
                rock->setScale(scaleX, scaleY); // Ensure consistent scaling
                m_objects.push_back(std::move(rock));
                break;
            }
            case 'D': {
                auto door = std::make_unique<Door>(GetTexture(DOOR));
                door->setPosition(position.x, position.y);
                door->setScale(scaleX, scaleY); // Ensure consistent scaling
                m_objects.push_back(std::move(door));
                break;
            }
            default:
                break;
            }
        }
    }

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
        {BOMB, "bomb.png"},
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
        m_robot->draw(window);
    
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

    // Update robot position and animation
    m_robot->update(deltaTime);
    //  handleCollisions();

    m_Toolbar.CallUpdateTimer();
    m_Toolbar.callUpdateToolbar(deltaTime);
       //*Update moving objects like guards/*
        for (auto& obj : m_movingObjects) {
            obj->update(deltaTime);
            sf::Vector2f objectPos = obj->getPosition();
            if (objectPos.x < leftBound) {
                //objectPos.x = leftBound;
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

            checkIfSmartGuard(obj.get());
        }
        // Remove bombs that are ready for removal
        m_movingObjects.erase(
            std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),
                [](const std::unique_ptr<MovingGameObject>& obj) {
                    auto* bomb = dynamic_cast<Bomb*>(obj.get());
                    return bomb && bomb->CanBeRemoved(); // Remove exploded bombs
                }),
            m_movingObjects.end()
        );

    // Boundary checks for the robot
    sf::Vector2f robotPos = m_robot->getPosition();


    // Ensure the robot stays within bounds
    if (robotPos.x < leftBound) {
        robotPos.x = leftBound;
    }
    else if (robotPos.x + m_cellSize.x > rightBound) {
        robotPos.x = rightBound - m_cellSize.x;
    }

    if (robotPos.y < topBound) {
        robotPos.y = topBound;
    }
    else if (robotPos.y + m_cellSize.y > bottomBound) {
        robotPos.y = bottomBound - m_cellSize.y;
    }

    // Apply corrected position
    m_robot->setPosition(robotPos.x, robotPos.y);
    handleCollisions();
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

void Board::handleCollisions() {
    sf::CircleShape robotShape = m_robot->getCollisionShape();

    // Track objects to remove
    std::vector<MovingGameObject*> movingObjectsToRemove;
    std::vector<GameObject*> staticObjectsToRemove;

    // Check collisions between the robot and static objects
    for (const auto& staticObject : m_objects) {
        if (robotShape.getGlobalBounds().intersects(staticObject->getBoundingBox())) {
            m_robot->handleCollision(*staticObject);
            staticObject->handleCollision(*m_robot);
        }
    }

    // Check collisions between the robot and moving objects
    for (const auto& movingObject : m_movingObjects) {
        const sf::Shape& movingShape = movingObject->getCollisionShape();

        if (robotShape.getGlobalBounds().intersects(movingShape.getGlobalBounds())) {
            m_robot->handleCollision(*movingObject);
            movingObject->handleCollision(*m_robot);
        }

        // Handle bomb explosions
        auto* bomb = dynamic_cast<Bomb*>(movingObject.get());
        if (bomb && bomb->CheckBombExplode()) {
            std::vector<sf::FloatRect> explosionBounds = bomb->getExplosionPlusShapeBounds();

            // Mark static objects (like rocks) for removal, excluding walls and doors
            for (const auto& obj : m_objects) {
                if (!dynamic_cast<Wall*>(obj.get()) && !dynamic_cast<Door*>(obj.get())) {
                    for (const auto& rect : explosionBounds) {
                        if (rect.intersects(obj->getBoundingBox())) {
                            bomb->handleCollision(*obj);
                            staticObjectsToRemove.push_back(obj.get());
                            break;
                        }
                    }
                }
            }

            // Mark moving objects (like guards) for removal, excluding bombs
            for (const auto& obj : m_movingObjects) {
                if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
                    const sf::Shape& objShape = obj->getCollisionShape();
                    for (const auto& rect : explosionBounds) {
                        if (rect.intersects(objShape.getGlobalBounds())) {
                            bomb->handleCollision(*obj);
                            movingObjectsToRemove.push_back(obj.get());
                            break;
                        }
                    }
                }
            }
        }

        // Check collisions between moving objects and static objects
        for (const auto& staticObject : m_objects) {
            if (movingShape.getGlobalBounds().intersects(staticObject->getBoundingBox())) {
                movingObject->handleCollision(*staticObject);
                staticObject->handleCollision(*movingObject);
            }
        }
    }

    // Check collisions between moving objects
    for (size_t i = 0; i < m_movingObjects.size(); ++i) {
        for (size_t j = i + 1; j < m_movingObjects.size(); ++j) { // Avoid duplicate checks
            const sf::Shape& shape1 = m_movingObjects[i]->getCollisionShape();
            const sf::Shape& shape2 = m_movingObjects[j]->getCollisionShape();

            if (shape1.getGlobalBounds().intersects(shape2.getGlobalBounds())) {
                m_movingObjects[i]->handleCollision(*m_movingObjects[j]);
                m_movingObjects[j]->handleCollision(*m_movingObjects[i]);
            }
        }
    }

    // Remove marked static objects
    m_objects.erase(
        std::remove_if(m_objects.begin(), m_objects.end(),
            [&staticObjectsToRemove](const std::unique_ptr<GameObject>& obj) {
                return std::find(staticObjectsToRemove.begin(), staticObjectsToRemove.end(), obj.get()) != staticObjectsToRemove.end();
            }),
        m_objects.end()
    );

    // Remove marked moving objects
    m_movingObjects.erase(
        std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),
            [&movingObjectsToRemove](const std::unique_ptr<MovingGameObject>& obj) {
                return std::find(movingObjectsToRemove.begin(), movingObjectsToRemove.end(), obj.get()) != movingObjectsToRemove.end();
            }),
        m_movingObjects.end()
    );
}






void Board::GenerateBomb() {
    auto bomb = std::make_unique<Bomb>(GetTexture(BOMB));
    sf::Vector2f robotPos = m_robot->getPosition();
    bomb->setPosition(robotPos.x, robotPos.y);

    // Get the collision shape of the new bomb
    sf::CircleShape newBombCollisionShape = bomb->getCollisionShape();

    // Check if the new bomb's collision shape overlaps with any existing bomb
    for (const auto& obj : m_movingObjects) {
        if (auto* existingBomb = dynamic_cast<Bomb*>(obj.get())) {
            // Get the collision shape of the existing bomb
            sf::CircleShape existingBombCollisionShape = existingBomb->getCollisionShape();

            // Check if the bounding boxes of the two collision shapes intersect
            if (newBombCollisionShape.getGlobalBounds().intersects(existingBombCollisionShape.getGlobalBounds())) {
                std::cout << "Cannot place bomb: Overlaps with an existing bomb.\n";
                return; // Bomb overlaps, do not place
            }
        }
    }

    // Add the bomb to the moving objects if no overlap
    m_movingObjects.push_back(std::move(bomb));
    std::cout << "Bomb placed successfully at: (" << robotPos.x << ", " << robotPos.y << ").\n";
}
