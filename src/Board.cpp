#include "Board.h"


Board::Board()
    : m_rows(0), m_cols(0),m_guardCount(0), m_FreezeGuardsStatus(false), m_pause(false), m_pausedByHit(false), m_levelComplete(false), m_lives(3), m_pauseDuration(2) {
    m_robot = std::make_unique<Robot>();
    srand(static_cast<unsigned int>(time(0)));
}


bool Board::loadFromFile(const std::string& fileName) {
    m_levelComplete = false;
    isGuardSmart(5);
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    m_rows = static_cast<int>(lines.size());
    m_cols = lines.empty() ? 0 : static_cast<int>(lines[0].size());

    float gridHeight = WINDOW_HEIGHT - TOOLBAR_HEIGHT; // Remaining height after the toolbar

    m_cellSize.x = WINDOW_WIDTH / static_cast<float>(m_cols);
    m_cellSize.y = gridHeight / static_cast<float>(m_rows);
    float scaleX = m_cellSize.x / SINGLE_SPRITE_DIMENSIONS;
    float scaleY = m_cellSize.y / SINGLE_SPRITE_DIMENSIONS;

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            sf::Vector2f position(j * m_cellSize.x, i * m_cellSize.y + TOOLBAR_HEIGHT); // Offset by toolbar height
            switch (symbol) {
            case '#': {
                auto wall = std::make_unique<Wall>();
                wall->setPosition(position.x, position.y);
                wall->setScale(scaleX, scaleY); // Ensure consistent scaling
                m_objects.push_back(std::move(wall));
                break;
            }
            case '/':
                m_robot->setPosition(position.x, position.y);
                std::cout << "Robot initial position: (" << position.x << ", " << position.y << ")\n";
                m_robotStartingPosition = sf::Vector2f(position.x, position.y);
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
                guard->setStartingPosition(position.x, position.y);

                // Scale guards based on individual frame dimensions
                float guardScaleX = m_cellSize.x / 127.5f;  // 127.5 = guard frame width
                float guardScaleY = m_cellSize.y / 163.33f; // 163.33 = guard frame height
                guard->setScale(guardScaleX, guardScaleY);
                m_movingObjects.push_back(std::move(guard));
                //  m_guardsStartingPositions.push_back(sf::Vector2f(position.x, position.y));

                m_guardCount++;
                break;
            }


            case '@': {
                auto rock = std::make_unique<Rock>();
                rock->setPosition(position.x, position.y);
                rock->setScale(scaleX, scaleY); // Ensure consistent scaling
                m_objects.push_back(std::move(rock));
                break;
            }
            case 'D': {
                auto door = std::make_unique<Door>();
                door->setPosition(position.x, position.y);
                door->setScale(scaleX, scaleY); // Ensure consistent scaling
                m_objects.push_back(std::move(door));
                break;
            }
            case ' ':
                // 20% chance to spawn a coin in empty space
                if (rand() % 10 == 0) { // 1 in 5 chance (adjust as needed)
                    auto coin = std::make_unique<Coin>();
                    coin->setPosition(position.x, position.y);
                    coin->setScale(15*scaleX, 15*scaleY);
                    m_objects.push_back(std::move(coin));
                }
                break;

           
            default:
                break;
            }

        }
    }
    return true;

}

bool Board::loadPresent(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << fileName << std::endl;
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    float scaleX = m_cellSize.x / SINGLE_SPRITE_DIMENSIONS;
    float scaleY = m_cellSize.y / SINGLE_SPRITE_DIMENSIONS;

    int maxAttempts = 10; // Limit the number of attempts to prevent infinite loops

    for (int attempts = 0; attempts < maxAttempts; ++attempts) {
        // Check if the present count exceeds the limit before generating a new one
        if (Present::getPresentCount() > NUM_PRESENT) {
            return false; // Stop trying if we already have 6 presents
        }

        int i = rand() % m_rows;
        int j = rand() % m_cols;

        sf::Vector2f position(j * m_cellSize.x, i * m_cellSize.y + TOOLBAR_HEIGHT);

        // Check if the space is empty and no present exists there
        if (lines[i][j] == ' ' && !isPresentAtPosition(position)) {
            int randomChance = rand() % 10; // 1 in 10 chance to place a present

            if (randomChance < 5) { // 50% chance to place a present
                int random = rand() % 4; // Random number to decide which present type

                std::unique_ptr<Present> present;
                switch (random) {
                case 0:
                    present = std::make_unique<FreezeGuard>();
                    break;
                case 1:
                    present = std::make_unique<ExtraLife>();
                    break;
                case 2:
                    present = std::make_unique<RemovedGuard>();
                    break;
                case 3:
                    present = std::make_unique<IncreaseTime>();
                    break;
                }

                if (present) {
                    present->setPosition(position.x, position.y);
                    present->setScale(scaleX, scaleY);
                    m_objects.push_back(std::move(present));
                    return true; // Exit after placing ONE present
                }
            }
        }
    }
    return false; // No suitable empty space found after attempts
}


bool Board::isPresentAtPosition(const sf::Vector2f& position) {
    for (const auto& obj : m_objects) {
        if (dynamic_cast<Present*>(obj.get())) {
            if (obj->getPosition() == position) {
                return true; // A present already exists at this position
            }
        }
    }
    return false;
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


void Board::PowerUp(const char choice) {
    switch (choice) {
        // 🧊 Freeze All Guards for 10 Seconds
    case 'F':
        for (const auto& obj : m_movingObjects) {
            if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
                guard->setFreezeGaurd(true);  // Freeze guard
            }
        }

        // Create a thread to unfreeze guards after 10 seconds
        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            for (const auto& obj : m_movingObjects) {
                if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
                    guard->setFreezeGaurd(false);  // Unfreeze guard
                }
         }
        }).detach();  // Detach the thread to avoid blocking

        std::cout << "All guards frozen for 3 seconds!" << std::endl;
        break;


    case 'L':
        m_Toolbar.IncreaseHeart(true);  // Assuming a function to add lives
        std::cout << "Extra life granted!" << std::endl;
        break;


    case 'R':
        for (auto it = m_movingObjects.begin(); it != m_movingObjects.end(); ++it) {
            if (dynamic_cast<Guard*>(it->get())) {
                m_movingObjects.erase(it);
                std::cout << "A guard has been removed!" << std::endl;
                m_Toolbar.addToScore(DEAD_GUARD_SCORE);
                break;  // Remove only one guard
            }
        }
        break;

        // ⏳ Increase Time
    case 'T':
        m_Toolbar.IncreaseTime(30);
        break;

    default:
        std::cout << "Invalid power-up choice!" << std::endl;
        break;
    }
}





//void Board::callUpdateToolbar(const float deltatime) {
//   // m_Toolbar.callUpdateToolbar(deltatime);
//    m_Toolbar.updateTimerDisplay(deltatime);
//}

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




void Board::display(sf::RenderWindow& window) {
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
int Board::update(float deltaTime, const int level) {



    if (m_pausedByHit) {
        if (m_pauseClock.getElapsedTime().asSeconds() >= m_pauseDuration) {
            m_pausedByHit = false;
            resetObjectsLocation();  // Reset robot & guards
            removeAllBombs();        // Remove bombs
            m_Toolbar.updateTimerDisplay(deltaTime);
           
        }
        else {
            std::cout << "Paused by hit. Waiting for 2 seconds..." << std::endl;
            return PLAYING;  // Skip updates while paused
        }
    }

    if (m_robot->isRobotHit()) {
        m_lives--;
        if (m_lives <= 0) return LOST_GAME;
        m_pauseClock.restart();  // Start pause timer
        m_pausedByHit = true;
        m_pause = true;
        m_robot->setHitStatus(false);
        m_Toolbar.IncreaseTime(3);
        m_Toolbar.updateTimerDisplay(deltaTime);
       
        return LOST_LIFE;
    }
    if (!m_Toolbar.getIsTimerRunning()) {
        return LOST_GAME;
    }

    // Normal game update logic
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        GenerateBomb();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
        m_levelComplete = true; // Generate a bomb when 'B' is pressed
    }

    for (const auto& object : m_objects) {
        if (auto* coin = dynamic_cast<Coin*>(object.get())) {
            coin->update(deltaTime);
        }
    }

    m_robot->update(deltaTime);
    m_Toolbar.updateTimerDisplay(deltaTime);

    // Timer for placing presents periodically (for example, every 5 seconds)
    static float timeElapsed = 0.0f;
    timeElapsed += deltaTime;

    if (timeElapsed >= 5.0f) {  // Every 5 seconds
        std::string levelFile = "level" + std::to_string(level) + ".txt";
        loadPresent(levelFile);  // Call the function to place presents
        timeElapsed = 0.0f;  // Reset the timer
    }

    // Use an iterator-based loop for safe removal
    for (auto it = m_movingObjects.begin(); it != m_movingObjects.end(); ) {
        auto* bomb = dynamic_cast<Bomb*>((*it).get());

        if (bomb && bomb->CanBeRemoved()) {
            std::cout << "Bomb removed!\n";
            it = m_movingObjects.erase(it); // Erase bomb & update iterator
        }
        else { // Ensure we only increment if not erased
            auto* guard = dynamic_cast<Guard*>((*it).get());
            if (guard && !guard->getIsFreeze()) {
                (*it)->update(deltaTime);
                checkIfSmartGuard((*it).get());
            }
            else if (!guard) {
                (*it)->update(deltaTime);
            }
            ++it; // Only increment if not erased
        }
    }

    handleCollisions();


    return PLAYING;
}






void Board::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (!isPressed) return; // Only process key press, not release

    if (m_robot) {
        m_robot->handleInput(key, isPressed); // Forward input to the robot
    }

    if (key == sf::Keyboard::B) {
        GenerateBomb(); // Generate a bomb when 'B' is pressed
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
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::CircleShape robotShape = m_robot->getCollisionShape();
    std::vector<MovingGameObject*> movingObjectsToRemove;
    std::vector<GameObject*> staticObjectsToRemove;

    // Check collisions between the robot and objects
    for (const auto& obj : m_objects) {
        if (robotShape.getGlobalBounds().intersects(obj->getBoundingBox())) {
            if (auto* door = dynamic_cast<Door*>(obj.get())) {
                m_levelComplete = true;
            }
            else if (auto* present = dynamic_cast<Present*>(obj.get())) {
                PowerUp(present->getSymbol());
                m_robot->handleCollision(*obj);
                staticObjectsToRemove.push_back(obj.get());
            }
            else {
                m_robot->handleCollision(*obj);
                obj->handleCollision(*m_robot);
            }
            // Check if the robot collides with a Coin
            if (auto* coin = dynamic_cast<Coin*>(obj.get())) {
                if (robotShape.getGlobalBounds().intersects(coin->getCollisionShape().getGlobalBounds())) {
                    // Handle coin collection (e.g., increase score)
                    m_Toolbar.addToScore(COIN_SCORE); 
                    sf::Sound& coinSound = resourceManager.getSound("coin");
                    coinSound.setVolume(25);
                    coinSound.play();
                    // Remove the coin from the game objects
                    staticObjectsToRemove.push_back(obj.get());

                    std::cout << "Coin collected!" << std::endl;
                }
            }
        }
    }

    // Check collisions between the robot and moving objects
    for (const auto& obj : m_movingObjects) {
        const sf::Shape& movingShape = obj->getCollisionShape();
        if (robotShape.getGlobalBounds().intersects(movingShape.getGlobalBounds())) {

            //erase heart
            if (dynamic_cast<Guard*>(obj.get())) {
                m_Toolbar.IncreaseHeart(false);
               // continue;
            }

            m_robot->handleCollision(*obj);
            obj->handleCollision(*m_robot);
        }

        // Handle bomb explosions
        if (auto* bomb = dynamic_cast<Bomb*>(obj.get()); bomb && bomb->CheckBombExplode()) {
            for (const auto& rect : bomb->getExplosionPlusShapeBounds()) {
                // Check if the robot is hit by the explosion
                if (rect.intersects(robotShape.getGlobalBounds())) {
                    std::cout << "Robot was hit by an explosion!" << std::endl;
                    m_robot->setHitStatus(true);
                    m_Toolbar.IncreaseHeart(false);
                }

                for (const auto& staticObj : m_objects)
                    if (dynamic_cast<Rock*>(staticObj.get()) && rect.intersects(staticObj->getBoundingBox()))
                        staticObjectsToRemove.push_back(staticObj.get());

                for (const auto& movingObj : m_movingObjects)
                    if (dynamic_cast<Guard*>(movingObj.get()) && rect.intersects(movingObj->getCollisionShape().getGlobalBounds())) {
                        movingObjectsToRemove.push_back(movingObj.get());
                        m_Toolbar.addToScore(DEAD_GUARD_SCORE);
                    }
            }
        }

        // Check collisions between moving and static objects
        for (const auto& staticObj : m_objects)
            if (movingShape.getGlobalBounds().intersects(staticObj->getBoundingBox())) {
                obj->handleCollision(*staticObj);
                staticObj->handleCollision(*obj);
            }
    }

    // Check collisions between moving objects
    for (size_t i = 0; i < m_movingObjects.size(); ++i)
        for (size_t j = i + 1; j < m_movingObjects.size(); ++j)
            if (m_movingObjects[i]->getCollisionShape().getGlobalBounds().intersects(m_movingObjects[j]->getCollisionShape().getGlobalBounds())) {
                m_movingObjects[i]->handleCollision(*m_movingObjects[j]);
                m_movingObjects[j]->handleCollision(*m_movingObjects[i]);
            }

    // Remove marked objects
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
        [&staticObjectsToRemove](const std::unique_ptr<GameObject>& obj) {
            return std::find(staticObjectsToRemove.begin(), staticObjectsToRemove.end(), obj.get()) != staticObjectsToRemove.end();
        }), m_objects.end());

    m_movingObjects.erase(std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),
        [&movingObjectsToRemove](const std::unique_ptr<MovingGameObject>& obj) {
            return std::find(movingObjectsToRemove.begin(), movingObjectsToRemove.end(), obj.get()) != movingObjectsToRemove.end();
        }), m_movingObjects.end());
}






void Board::GenerateBomb() {
    auto bomb = std::make_unique<Bomb>();
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
               // std::cout << "Cannot place bomb: Overlaps with an existing bomb.\n";
                return; // Bomb overlaps, do not place
            }
        }
    }

    // Add the bomb to the moving objects if no overlap
    m_movingObjects.push_back(std::move(bomb));
   // std::cout << "Bomb placed successfully at: (" << robotPos.x << ", " << robotPos.y << ").\n";
}

void Board::resetObjectsLocation() {
    // Reset robot's position
    m_robot->setPosition(m_robotStartingPosition.x, m_robotStartingPosition.y);

    // Reset guards' positions
    for (const auto& obj : m_movingObjects) {
        if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
            guard->setPosition(guard->getStartingPosition().x, guard->getStartingPosition().y);
        }
    }
}

void Board::setPause() {
    m_pause = false;
}

void Board::removeAllBombs() {
    m_movingObjects.erase(
        std::remove_if(m_movingObjects.begin(), m_movingObjects.end(),
            [](const std::unique_ptr<MovingGameObject>& obj) {
                return dynamic_cast<Bomb*>(obj.get()) != nullptr;
            }),
        m_movingObjects.end()
    );
}
void Board::startTimer() {
    m_Toolbar.startTimer();
}

bool Board::isLevelComplete() {
    if (m_levelComplete) {
        m_objects.clear();
        m_movingObjects.clear();
        m_Toolbar.setTimer(120);
        m_Toolbar.addToScore(LEVEL_COMPLETE_SCORE + m_guardCount * GUARDS_PER_LEVEL_SCORE);
        std::cout << "Level complete! Score: " << m_guardCount << std::endl;
        m_guardCount = 0;

        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Next Level");
        window.clear(sf::Color::Black);
        window.display();

        return true;
    }
    return false;
}




//todo change this function according to resource manager
void Board::showTransitionScreen(sf::RenderWindow& window, const std::string& message, sf::Color backgroundColor) {
    // Create overlay
    sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(backgroundColor);

    // Load font (ensure you have a font file)
    static sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    // Create text
    sf::Text text;
    text.setFont(font);
    text.setString(message);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 50); // Centered

    // Display transition screen for 2 seconds
    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2) {
        window.clear();
        window.draw(overlay);
        window.draw(text);
        window.display();
    }
}
