#include "Board.h"



Board::Board()
    : m_rows(0), m_cols(0), m_FreezeGuardsStatus(false), m_lives(0), m_LevelDuration(0.0f), m_TimeLeft(0.0f), m_isTimerRunning(true) {
    m_clock.restart();  // Start the clock immediately
    loadTextures();
    //Board::UploadSound();
}

//void Board::UploadSound() {
//    if (!m_BackgroundGameTexture.loadFromFile("helpBackground.png")) {
//        std::cerr << "Error loading help menu background!" << std::endl;
//    }
//    m_BackgroundGameSprite.setTexture(m_BackgroundGameTexture);
//}



void Board::PowerUp(const powerUps choice) {
    switch (choice) {
    case FreezeGuards:
        FreezeAllGuards(true);  // Freeze all guards
        std::cout << "All guards have been frozen!" << std::endl;
        break;
    case ExtraLife:
        GrantExtraLife();  // Grant an extra life
        std::cout << "An extra life has been granted!" << std::endl;
        break;
    case RemovedGuard:
        //RemoveGuard();  // Remove a guard
        std::cout << "A guard has been removed!" << std::endl;
        break;
    case TimeIncrease:
        IncreaseTime(30);  // Increase time by 30 seconds
        std::cout << "Time has been increased!" << std::endl;
        break;
    default:
        std::cout << "Invalid power-up choice!" << std::endl;
        break;
    }
}

void Board::FreezeAllGuards(const bool status) {
    m_FreezeGuardsStatus = status;
    if (status) {
        std::cout << "Guards are now frozen." << std::endl;
        // Add logic to freeze all guards
    }
    else {
        std::cout << "Guards are no longer frozen." << std::endl;
        // Unfreeze all guards (resume movement)
    }
}

void Board::GrantExtraLife() {
    m_lives++;  // Grant an extra life
}





void Board::IncreaseTime(const int extraTime) {
    m_TimeLeft += extraTime;  // Add extra time
    if (m_TimeLeft > m_LevelDuration) {
        m_TimeLeft = m_LevelDuration;  // Cap the time at the level duration
    }
    std::cout << "Time increased by " << extraTime << " seconds." << std::endl;
}




//functions for timer
void Board::UpdateTimer() {
    if (m_isTimerRunning) {
        sf::Time elapsed = m_clock.getElapsedTime();  // Get elapsed time from clock
        m_TimeLeft = m_LevelDuration - elapsed.asSeconds();  // Calculate remaining time

        if (m_TimeLeft <= 0) {
            m_TimeLeft = 0;
            m_isTimerRunning = false;  // Stop the timer if time runs out
            std::cout << "Time's up!" << std::endl;
        }
    }
}

std::string Board::getTimeString() const {
    int minutes = static_cast<int>(m_TimeLeft) / 60;
    int seconds = static_cast<int>(m_TimeLeft) % 60;
    std::ostringstream oss;
    oss << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    return oss.str();
}



void Board::setLevelDuration(const float duration) {
    m_LevelDuration = duration;
    m_TimeLeft = duration;
    m_isTimerRunning = true;  // Ensure the timer is running
    m_clock.restart();  // Restart the clock
}

// Get the time left for the level
float Board::getTimeLeft() const {
    return m_TimeLeft;
}

// Get the total level duration
float Board::getLevelDuration() const {
    return m_LevelDuration;
}
void Board::CallUpdateTimer() {
    UpdateTimer();
}
void Board::setTimer(const float duration)  {
    setLevelDuration(duration);
}





void Board::updateTimerDisplay(sf::Text& timerText, sf::RectangleShape& progressBar, sf::Sprite& arrow,std::vector<sf::Sprite>& heart, const float deltaTime) {
    // Update the timer first (call your UpdateTimer() method)
    CallUpdateTimer();



    // Get the time left
    float timeLeft = getTimeLeft();


    

    // Update the time left as a string
    std::string timeText = "Time Left: " + getTimeString();
    timerText.setString(timeText);

    // Heartbeat effect on the timer text (pulsing)
    if (timeLeft <= 10) { // Apply heartbeat effect only when time is low
        float scaleFactor = 1.0f + 0.1f * sin(3.f * timeLeft);  // Sinusoidal pulse effect
        timerText.setScale(scaleFactor, scaleFactor);  // Scale the text
    }
    else {
        timerText.setScale(1.f, 1.f);  // Reset scale when time is not critical
    }

    // Fading Text Effect & Change Progress Bar Color
    if (timeLeft > 30) {
        timerText.setFillColor(sf::Color(255, 255, 255, 255));  // Full opacity for fading effect
        progressBar.setFillColor(sf::Color::Green);  // Progress bar green
    }
    else if (timeLeft > 10) {
        timerText.setFillColor(sf::Color(255, 255, 255, 150));  // Slightly faded text
        progressBar.setFillColor(sf::Color::Yellow);  // Progress bar yellow
    }
    else {
        timerText.setFillColor(sf::Color(255, 0, 0, 255));  // Red text for urgency
        progressBar.setFillColor(sf::Color::Red);  // Progress bar red
    }

    // Rotation Effect: Rotate the timer text as the time gets closer to 0
    float rotationSpeed = 30.f * (1.f - (timeLeft / m_LevelDuration));  // Increase speed as time runs out
    timerText.setRotation(rotationSpeed * deltaTime);

    // Smoothly animate the progress bar based on time left
    animateProgressBar(deltaTime, progressBar);

    // Update the rotation of the clock hand (robot texture)
    float clockRotation = (1.0f - (timeLeft / m_LevelDuration)) * 360.f;  // Rotate based on time remaining
    arrow.setRotation(clockRotation);  // Apply the calculated rotation to the clock hand

    float heartscale =  0.3f * sin(3.f * timeLeft);;
    for (int pos = 0; pos < heart.size(); pos++) {
        heart[pos].setScale(heartscale, heartscale);  // Scale the text
    }
   
}


void Board::animateProgressBar(float deltaTime, sf::RectangleShape& progressBar) const {
    float timeLeft = getTimeLeft();
    float levelDuration = getLevelDuration();

    // Calculate the target width based on remaining time
    float targetWidth = 200.f * (timeLeft / levelDuration);
    float currentWidth = progressBar.getSize().x;

    // Smooth transition of width change
    float smoothTransition = currentWidth + (targetWidth - currentWidth) * deltaTime * 5.f;  // The factor "5.f" controls the smoothness
    progressBar.setSize(sf::Vector2f(smoothTransition, 10.f));
}











const sf::Texture& Board::GetTexture(const int chice) const
{
    return m_textures[chice];
}

void Board::SetSprite(sf::Sprite& picture,const float POSx, const float POSy,const float thicknes) const  {
    picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);  // Set origin to center of the sprite
    picture.setPosition(POSx, POSy);  // Positioning the clock hand (adjust position as needed)
    picture.setScale(thicknes, thicknes);  // Uniform scaling for both axes (width and height)
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
    m_grid.resize(m_rows, std::vector<Cell>(m_cols));

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            switch (symbol) {
            case '#':
                m_grid[i][j].content = new Wall();
                m_grid[i][j].isWalkable = false;
                break;
            case ' ':
                m_grid[i][j].content = new Empty();
                m_grid[i][j].isWalkable = true;
                break;
            case '/':
                m_grid[i][j].content = new Robot();
                m_grid[i][j].isWalkable = false;
                m_robotPosition = { static_cast<float>(j), static_cast<float>(i) };
                break;
            case '!':
                m_grid[i][j].content = new Guard();
                m_grid[i][j].isWalkable = false;
                break;
            case '@':
                m_grid[i][j].content = new Rock();
                m_grid[i][j].isWalkable = false;
                break;
            case 'D':
                m_grid[i][j].content = new Door();
                m_grid[i][j].isWalkable = false;
                break;
            default:
                m_grid[i][j].content = nullptr;
                break;
            }
        }
    }
}

void Board::loadTextures() {
    m_textures.resize(TEXTURE_COUNT);
    const std::map<int, std::string> textureFiles = {
        {WALL, "wall.png"},
        {ROCK, "rock.png"},
        {GUARD, "guard.png"},
        {DOOR, "door.png"},
        {EMPTY, "empty.png"},
        {HEART,"heart.png"},
         {CLOCK,"Clock.png"},
         {ARROW, "arrow.png"}
    };

    for (const auto& [index, filename] : textureFiles) {
        std::cout << index << std::endl;
        if (!m_textures[index].loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        }
    }
}

void Board::display(sf::RenderWindow& window) const {
    if (m_rows == 0 || m_cols == 0) return;

    float frameWidth = window.getSize().x * 0.8f;
    float frameHeight = window.getSize().y * 0.8f;
    float cellWidth = frameWidth / m_cols;
    float cellHeight = frameHeight / m_rows;

    float offsetX = (window.getSize().x - frameWidth) / 2.0f;
    float offsetY = (window.getSize().y - frameHeight) / 2.0f;

    sf::View view(sf::FloatRect(0, 0, frameWidth, frameHeight));
    view.setViewport(sf::FloatRect(offsetX / window.getSize().x, offsetY / window.getSize().y, frameWidth / window.getSize().x, frameHeight / window.getSize().y));
    window.setView(view);

    sf::Sprite sprite;
    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (m_grid[i][j].content) {
                const sf::Texture* texture = nullptr;
                char symbol = m_grid[i][j].content->getSymbol();
                switch (symbol) {
                case '#': texture = &m_textures[WALL]; break;
                case ' ': texture = &m_textures[EMPTY]; break;
                case '/': texture = &m_textures[ROBOT]; break;
                case '!': texture = &m_textures[GUARD]; break;
                case 'D': texture = &m_textures[DOOR]; break;
                case '@': texture = &m_textures[ROCK]; break;
                default: continue;
                }

                if (texture) {
                    sprite.setTexture(*texture);
                    sprite.setScale(cellWidth / sprite.getTexture()->getSize().x, cellHeight / sprite.getTexture()->getSize().y);
                    sprite.setPosition(j * cellWidth, i * cellHeight);
                    window.draw(sprite);
                }
            }
        }
    }

    window.setView(window.getDefaultView());
}


void Board::displayConsole() const {
    for (const auto& row : m_grid) {
        for (const auto& cell : row) {
            if (cell.content) {
                std::cout << cell.content->getSymbol();
            }
            else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}
sf::Vector2f Board::getRobotPosition() const {
    return { m_robotPosition.x , m_robotPosition.y };  // Returns the robot's position
}
