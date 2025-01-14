#include "Board.h"


Board::Board()
    : m_rows(0), m_cols(0), m_FreezeGuardsStatus(false), m_lives(0), m_LevelDuration(0.0), m_TimeLeft(0.0), m_isTimerRunning(true) {
    // Initialize timer and set it to running
    m_clock.restart();  // Starts the clock immediately

}
//this is for the timer 
// Optional: Use the clock to update the TimeLeft in each frame (could be in an update function)
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
void Board::PowerUp(const object choice) {
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
        IncreaseTime(30);  // Increase time by 30 seconds, for example
        std::cout << "Time has been increased!" << std::endl;
        break;

    default:
        std::cout << "Invalid power-up choice!" << std::endl;
        break;
    }
}

// Implementation of FreezeAllGuards
void Board::FreezeAllGuards(const bool status) {
    m_FreezeGuardsStatus = status;
    if (status) {
        std::cout << "Guards are now frozen." << std::endl;
        // Add logic to freeze all guards in the game 
    }
    else {
        std::cout << "Guards are no longer frozen." << std::endl;
        // Add logic to unfreeze all guards (e.g., resume their movement)
    }
}

// Grant an extra life
void Board::GrantExtraLife() {
    // Logic to grant an extra life (you can add an attribute for the number of lives)
    m_lives++;  // Assuming you have a lives attribute
}

// Remove a guard from the board
//void Board::RemoveGuard() {
//     Logic for removing a guard (you can reduce the number of active guards)
//    if (!guards.empty()) {
//        guards.pop_back();  // Assuming you have a list of guards and you remove the last one
//    }
//    else {
//        std::cout << "No guards to remove." << std::endl;
//    }
//}



//this is for the timer 
// Increase the remaining time (e.g., add more time to the level)
void Board::IncreaseTime(const  int extraTime) {
    m_TimeLeft += extraTime;  // Add extra time to the remaining time
    if (m_TimeLeft > m_LevelDuration) {
        m_TimeLeft = m_LevelDuration;  // Cap time to the max level duration
    }
    std::cout << "Time increased by " << extraTime << " seconds." << std::endl;
}



//this is for the timer 
//addddd
// Get the remaining time as a string
std::string Board::getTimeString() const {
    int minutes = static_cast<int>(m_TimeLeft) / 60;
    int seconds = static_cast<int>(m_TimeLeft) % 60;
    std::ostringstream oss;
    oss << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    return oss.str();
}
void Board::setLevelDuration(float duration) {
    m_LevelDuration = duration;  // Set the level duration
    m_TimeLeft = duration;       // Initialize the remaining time
    m_isTimerRunning = true;     // Ensure the timer is running
    m_clock.restart();           // Restart the clock to begin timing
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
    grid.resize(m_rows, std::vector<Cell>(m_cols));

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            char symbol = lines[i][j];
            switch (symbol) {
            case '#':
                grid[i][j].content = new Wall();
                grid[i][j].isWalkable = false;
                grid[i][j].isExplodable = false;
                break;
            case ' ':
                grid[i][j].content = new Empty();
                grid[i][j].isWalkable = true;
                grid[i][j].isExplodable = false;
                break;
            default:
                std::cerr << "Unknown symbol '" << symbol << "' at (" << i << ", " << j << ")" << std::endl;
                grid[i][j].content = nullptr;
                break;
            }
        }
    }
}

void Board::loadTextures() {
    if (!wallTexture.loadFromFile("wall.png") || !emptyTexture.loadFromFile("empty.png")) {
        std::cerr << "Error: Failed to load textures." << std::endl;
    }
}

void Board::displayConsole() const {
    for (const auto& row : grid) {
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

void Board::display(sf::RenderWindow& window) const {
    if (m_rows == 0 || m_cols == 0) return;

    // Calculate frame and grid size
    float frameWidth = window.getSize().x * 0.8f;  // 80% of window width
    float frameHeight = window.getSize().y * 0.8f; // 80% of window height
    float cellWidth = frameWidth / static_cast<float>(m_cols);
    float cellHeight = frameHeight / static_cast<float>(m_rows);

    // Calculate frame top-left corner for centering
    float frameX = (window.getSize().x - frameWidth) / 2.0f;
    float frameY = (window.getSize().y - frameHeight) / 2.0f;

    // Define a view for the grid
    sf::View view(sf::FloatRect(0, 0, frameWidth, frameHeight));
    view.setViewport(sf::FloatRect(frameX / window.getSize().x, frameY / window.getSize().y,
        frameWidth / window.getSize().x, frameHeight / window.getSize().y));
    window.setView(view);

    // Draw the grid content
    sf::Sprite sprite;

    for (int i = 0; i < m_rows; ++i) {
        for (int j = 0; j < m_cols; ++j) {
            if (grid[i][j].content) {
                if (grid[i][j].content->getSymbol() == '#') {
                    sprite.setTexture(wallTexture);
                }
                else if (grid[i][j].content->getSymbol() == ' ') {
                    sprite.setTexture(emptyTexture);
                }

                // Scale sprite to fit the cell
                sprite.setScale(cellWidth / sprite.getTexture()->getSize().x,
                    cellHeight / sprite.getTexture()->getSize().y);

                // Position sprite inside the grid
                sprite.setPosition(j * cellWidth, i * cellHeight);

                // Draw the sprite
                window.draw(sprite);
            }
        }
    }

    // Reset the window's view to default after drawing the grid
    window.setView(window.getDefaultView());


}


