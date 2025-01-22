#include "Board.h"


Board::Board()
    : m_rows(0), m_cols(0), m_FreezeGuardsStatus(false), m_lives(0) {
    m_robot = std::make_unique<Robot>();
    loadTextures();
}

void Board::loadFromFile(const std::string& fileName) {
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

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            sf::Vector2f position(static_cast<float>(j), static_cast<float>(i));
            switch (symbol) {
            case '#':
              //  m_objects.push_back(std::make_unique<Wall>(position));
                break;
            case '/':
                   m_robot->setPosition(position.x, position.y);
                break;
            case '!':
              //  m_movingObjects.push_back(std::make_unique<Guard>(position));
                break;
            case '@':
               // m_objects.push_back(std::make_unique<Rock>(position));
                break;
            case 'D':
                //m_objects.push_back(std::make_unique<Door>(position));
                break;
            default:
                break;
            }
        }
    }
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

void Board::display(sf::RenderWindow& window) const {
    sf::Sprite sprite;

    for (const auto& obj : m_objects) {
        sprite.setTexture(GetTexture(obj->getSymbol()));
        sprite.setPosition(obj->getPosition());
        sprite.setScale(m_cellSize.x / sprite.getTexture()->getSize().x,
            m_cellSize.y / sprite.getTexture()->getSize().y);
        window.draw(sprite);
    }

    for (const auto& obj : m_movingObjects) {
        sprite.setTexture(GetTexture(obj->getSymbol()));
        sprite.setPosition(obj->getPosition());
        sprite.setScale(m_cellSize.x / sprite.getTexture()->getSize().x,
            m_cellSize.y / sprite.getTexture()->getSize().y);
        window.draw(sprite);
    }

    m_robot->draw(window); // Draw the robot
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
    for (auto& obj : m_movingObjects) {
        obj->update(deltaTime); // Update guards and other moving objects
    }
    m_robot->update(deltaTime); // Update robot position and animation
}

void Board::handleInput(sf::Keyboard::Key key, bool isPressed) {
    m_robot->handleInput(key, isPressed); // Handle input for robot
}