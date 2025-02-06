#include "Board.h"

Board::Board()
    : m_rows(0), m_cols(0),m_guardCount(0), m_pause(false), m_pausedByHit(false), m_levelComplete(false), m_lives(NUM_OF_LIVES) {
    m_robot = std::make_unique<Robot>();
    srand(static_cast<unsigned int>(time(0)));
}

bool Board::loadFromFile(const std::string& fileName, int level) {
    m_Toolbar.setTimer(LEVEL_DURATION);
    m_currentLevel = level;
    m_levelComplete = false;
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

    float gridHeight = WINDOW_HEIGHT - TOOLBAR_HEIGHT;

    m_cellSize.x = WINDOW_WIDTH / static_cast<float>(m_cols);
    m_cellSize.y = gridHeight / static_cast<float>(m_rows);
    float scaleX = m_cellSize.x / SINGLE_SPRITE_DIMENSIONS;
    float scaleY = m_cellSize.y / SINGLE_SPRITE_DIMENSIONS;

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            sf::Vector2f position(j * m_cellSize.x, i * m_cellSize.y + TOOLBAR_HEIGHT); 
            switch (symbol) {
            case '#': {
                auto wall = std::make_unique<Wall>();
                wall->setPosition(position.x, position.y);
                wall->setScale(scaleX, scaleY); 
                m_objects.push_back(std::move(wall));
                break;
            }
            case '/':
                m_robot->setPosition(position.x, position.y);
                m_robotStartingPosition = sf::Vector2f(position.x, position.y);
                break;

            case '!': {
                std::unique_ptr<Guard> guard;

                if (isGuardSmart()) {
                   
                    guard = std::make_unique<SmartGuard>(); 
                }
                else {
                   
                    guard = std::make_unique<StupidGuard>();  
                }

                guard->setPosition(position.x, position.y);
                guard->setStartingPosition(position.x, position.y);

                float guardScaleX = m_cellSize.x / GUARD_WIDTH;  
                float guardScaleY = m_cellSize.y / GUARD_HEIGHT; 
                guard->setScale(guardScaleX, guardScaleY);
                m_movingObjects.push_back(std::move(guard));

                m_guardCount++;
                break;
            }

            case '@': {
                auto rock = std::make_unique<Rock>();
                rock->setPosition(position.x, position.y);
                rock->setScale(scaleX, scaleY);
                m_objects.push_back(std::move(rock));
                break;
            }

            case 'D': {
                auto door = std::make_unique<Door>();
                door->setPosition(position.x, position.y);
                door->setScale(scaleX, scaleY); 
                m_objects.push_back(std::move(door));
                break;
            }

            case ' ':
                // 10% chance to spawn a coin in empty space
                if (rand() % 10 == 0) {
                    auto coin = std::make_unique<Coin>();
                    coin->setPosition(position.x, position.y);
                    coin->setScale(COIN_SCALE*scaleX, COIN_SCALE *scaleY);
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

    for (int attempts = 0; attempts < MAX_ATTEMPTS; ++attempts) {
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
                int random = rand() % NUM_OF_PRESENTS; // Random number to decide which present type
               
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

// Function to decide if a guard is smart
bool Board::isGuardSmart() {
    int intelligence = rand() % 100 + 1;
    int probability = std::min(100, m_currentLevel * 10);

    return intelligence < probability;
}

void Board::PowerUp(const char choice) {
    switch (choice) {
    case 'F':
        m_Toolbar.ShowPresent('F');
        for (const auto& obj : m_movingObjects) {
            if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
                guard->setFreezeGaurd(true);  
            }
        }
        
        // Create a thread to unfreeze guards after 10 seconds
        std::thread([this]() {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            for (const auto& obj : m_movingObjects) {
                if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
                    guard->setFreezeGaurd(false);  
                }
         }
        }).detach();  // Detach the thread to avoid blocking
        break;

    case 'L':
        m_Toolbar.ShowPresent('L');
        m_Toolbar.IncreaseHeart(true); 
        break;

    case 'R':

        m_Toolbar.ShowPresent('R');
        for (auto it = m_movingObjects.begin(); it != m_movingObjects.end(); ++it) {
            if (dynamic_cast<Guard*>(it->get())) {
                m_movingObjects.erase(it);
                m_Toolbar.addToScore(DEAD_GUARD_SCORE);
                break;  
            }
        }
        break;

    case 'T':
        m_Toolbar.IncreaseTime(10);
        m_Toolbar.ShowPresent('T');
        break;

    default:
        break;
    }
}

void Board::display(sf::RenderWindow& window) {

    m_Toolbar.draw(window);

    for (const auto& obj : m_objects) {
        obj->draw(window);
    }

    for (const auto& obj : m_movingObjects) {
        obj->draw(window);
    }
    m_robot->draw(window);
}

int Board::update(float deltaTime) {

    if (m_pause) {
        return PLAYING;
    }

    if (m_pausedByHit) {
        if (m_pauseClock.getElapsedTime().asSeconds() >= PAUSE_DURATION) {
            m_pausedByHit = false;
            resetObjectsLocation(); 
            removeAllBombs();      
            m_Toolbar.updateTimerDisplay(deltaTime);
            return PLAYING;
           
        }
        // else { not needed
        //     return PLAYING;  
        //     }
    }

    if (m_robot->isRobotHit()) {
        m_lives--;
        if (m_lives <= 0) return LOST_GAME;
        m_pauseClock.restart();  
        m_pausedByHit = true;
        m_robot->setHitStatus(false);
         m_Toolbar.IncreaseTime(3);        
          m_Toolbar.updateTimerDisplay(deltaTime);
       
        return LOST_LIFE;
    }
    if (!m_Toolbar.getIsTimerRunning()) {
        //player has run out of time as a result he loses all his score
        removeAllBombs();
        m_Toolbar.addToScore(-m_Toolbar.getScore());
        return TIMES_UP;
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

    static float timeElapsed = 0.0f;
    timeElapsed += deltaTime;

    if (timeElapsed >= 5.0f) {  // Every 5 seconds
        std::string levelFile = "level" + std::to_string(m_currentLevel) + ".txt";
        loadPresent(levelFile);  // Call the function to place presents
        timeElapsed = 0.0f;  // Reset the timer
    }

    for (auto it = m_movingObjects.begin(); it != m_movingObjects.end(); ) {
        auto* bomb = dynamic_cast<Bomb*>((*it).get());

        if (bomb && bomb->CanBeRemoved()) {
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

void Board::checkIfSmartGuard(MovingGameObject* obj) {
    if (auto* smartGuard = dynamic_cast<SmartGuard*>(obj)) {
        smartGuard->setPlayerPosition(m_robot->getPosition());
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
                    m_Toolbar.addToScore(COIN_SCORE); 
                    sf::Sound& coinSound = resourceManager.getSound("coin");
                    coinSound.setVolume(15);
                    coinSound.play();
                    staticObjectsToRemove.push_back(obj.get());
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
            }
            m_robot->handleCollision(*obj);
            obj->handleCollision(*m_robot);
        }

        // Handle bomb explosions
        if (auto* bomb = dynamic_cast<Bomb*>(obj.get()); bomb && bomb->CheckBombExplode()) {
            for (const auto& rect : bomb->getExplosionPlusShapeBounds()) {
                // Check if the robot is hit by the explosion
                if (rect.intersects(robotShape.getGlobalBounds())) {
                    m_robot->setHitStatus(true);
                    m_Toolbar.IncreaseHeart(false);
                }

                for (const auto& staticObj : m_objects)
                    if (dynamic_cast<Rock*>(staticObj.get()) && rect.intersects(staticObj->getBoundingBox()))
                        staticObjectsToRemove.push_back(staticObj.get());

                for (const auto& movingObj : m_movingObjects)
                    if (dynamic_cast<Guard*>(movingObj.get()) && rect.intersects(movingObj->getCollisionShape().getGlobalBounds())) {
                        sf::Sound& enemyKillSound = resourceManager.getSound("enemyKill");
                        enemyKillSound.setVolume(25);
                        enemyKillSound.play();
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

    m_movingObjects.push_back(std::move(bomb));
}

void Board::resetObjectsLocation() {
    m_robot->setPosition(m_robotStartingPosition.x, m_robotStartingPosition.y);

    for (const auto& obj : m_movingObjects) {
        if (auto* guard = dynamic_cast<Guard*>(obj.get())) {
            guard->setPosition(guard->getStartingPosition().x, guard->getStartingPosition().y);
            std::cout << "Guard reset to: (" << guard->getPosition().x << ", " << guard->getPosition().y << ").\n";
        }
    }
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
        m_Toolbar.setLevel(m_currentLevel + 1);
        m_Toolbar.addToScore(LEVEL_COMPLETE_SCORE + m_guardCount * GUARDS_PER_LEVEL_SCORE);
        m_guardCount = 0;

        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Next Level");
        window.clear(sf::Color::Black);
        window.display();

        return true;
    }
    return false;
}

void Board::togglePause() {
    m_pause = !m_pause;

    if (m_pause) {
        m_Toolbar.pauseTimer(); // Pause the timer
    }
    else {
        m_Toolbar.resumeTimer(); // Resume the timer
    }
}

void Board::reset() {
    m_objects.clear();         // Clear static objects
    m_movingObjects.clear();   // Clear moving objects
    m_guardCount = 0;          // Reset guard count
    m_robot->setPosition(m_robotStartingPosition.x, m_robotStartingPosition.y); // Reset robot position
    m_Toolbar.setTimer(LEVEL_DURATION);   // Reset timer
    m_Toolbar.addToScore(-m_Toolbar.getScore());
    m_Toolbar.setLevel(1);      // Reset level
    m_robot->setHitStatus(false);
    m_lives = 3;
    for(int createLives = 0; createLives < m_lives; createLives++){
        m_Toolbar.IncreaseHeart(true);
	}
}

bool Board::isPaused() {
    return m_pause;
}
