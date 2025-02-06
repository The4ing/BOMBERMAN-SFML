#include "ToolbarGame.h"

ToolbarGame::ToolbarGame()
    : m_isTimerRunning(true), m_LevelDuration(0), m_TimeLeft(0),m_score(0), m_isMuted(false), m_num_heart(0), m_isPaused(false){
    m_clock.restart();
    setTimer(120.f);
    ResourceManager& resourceManager = ResourceManager::getInstance();

    // Set up timer text
    sf::Text timerText;
    timerText.setFont(resourceManager.getFont("digit.ttf"));
    timerText.setCharacterSize(30);
    timerText.setOutlineThickness(4);
    timerText.setStyle(sf::Text::Bold);
    timerText.setPosition(80.f, 32.f);
    timerText.setScale(1.f, 1.f);
    timerText.setLetterSpacing(2.f);
    resourceManager.addText("timer", timerText);

    // Set up score text
    m_scoreText.setFont(resourceManager.getFont("digit.ttf")); 
    m_scoreText.setCharacterSize(40); 
    m_scoreText.setOutlineThickness(3);
    m_scoreText.setStyle(sf::Text::Bold);
    m_scoreText.setFillColor(sf::Color::White);  
    m_scoreText.setPosition(WINDOW_WIDTH / 2 + 150.f, 30.f); 
    m_scoreText.setString("Score: 0");  

    //set up level text
    m_levelText.setFont(resourceManager.getFont("digit.ttf"));
    m_levelText.setCharacterSize(40);  
    m_levelText.setOutlineThickness(3);
    m_levelText.setStyle(sf::Text::Bold);
    m_levelText.setFillColor(sf::Color::White); 
    m_levelText.setPosition(WINDOW_WIDTH / 2 - 300.f, 30.f); 
    m_levelText.setString("Level: 1");  

    // Set up timer sprite
    m_timer.setTexture(resourceManager.getTexture("timer.png"));
    m_timer.setOrigin(m_timer.getGlobalBounds().width / 2, m_timer.getGlobalBounds().height / 2);  
    m_timer.setPosition(105.f, 50.f);
    m_timer.setScale(0.4f, 0.4f);

    m_muteButton.setTexture(resourceManager.getTexture("unmute.png"));
    m_muteButton.setScale(0.1f, 0.1f);
    m_muteButton.setPosition(1850.f, 10.f);
    
    m_heart.resize(NUM_HEART);  // Reserve space for 3 sprites

    for (int i = 0; i < NUM_HEART; ++i) {
        std::string heartKey = "heart" + std::to_string(i);
        m_heart[i].setTexture(resourceManager.getTexture("heart.png"));
        m_heart[i].setOrigin(m_heart[i].getGlobalBounds().width / 2, m_heart[i].getGlobalBounds().height / 2);
        m_heart[i].setPosition(1750.f - i * 40.f, 50.f);
        m_heart[i].setScale(0.3f, 0.3f);
        m_num_heart++;
    }
}

const int ToolbarGame::getHeartCount() const 
{
    return m_num_heart;
}

void ToolbarGame::addToScore(int addedScore)
{
    m_score += addedScore;
    m_scoreText.setString("Score: " + std::to_string(m_score));  // Update text
}

void ToolbarGame::IncreaseHeart(const bool add) {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    if (getHeartCount() < 4 && add) {
        std::string heartKey = "heart" + std::to_string(getHeartCount());
        sf::Sprite newHeart;
        newHeart.setTexture(resourceManager.getTexture("heart.png"));
        newHeart.setOrigin(newHeart.getGlobalBounds().width / 2, newHeart.getGlobalBounds().height / 2);
        newHeart.setPosition(1750.f - getHeartCount() * 40.f, 50.f);
        newHeart.setScale(0.3f, 0.3f);
        m_heart.push_back(newHeart);
        m_num_heart++;
    }
    else if (!add && !m_heart.empty()) {
        m_num_heart--;  
        m_heart.pop_back();
    }
}

void ToolbarGame::draw(sf::RenderWindow& window) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    
    for (const auto& heart : m_heart) {
        window.draw(heart);
    }

    window.draw(m_timer);
    window.draw(m_progressBar);
    window.draw(resourceManager.getText("timer"));
    window.draw(m_muteButton);
    window.draw(m_scoreText);  
    window.draw(m_levelText);  

    if (m_presentClock.getElapsedTime().asSeconds() < 2.0f) {
        window.draw(m_presentText);
    }
}

void ToolbarGame::IncreaseTime(const int extraTime) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Text& timerText = resourceManager.getText("timer");

    m_TimeLeft += extraTime;  
    if (m_TimeLeft > MAX_TIME) {
        m_TimeLeft = MAX_TIME;  
    }
    m_LevelDuration = m_TimeLeft;  
    m_clock.restart(); 
    timerText.setString(getTimeString());
}

void ToolbarGame::UpdateTimer() {
    if (m_isPaused) return; // Skip updating time when paused

    if (m_isTimerRunning) {
        float elapsed = m_clock.getElapsedTime().asSeconds();
        m_TimeLeft = std::max(0.0f, m_LevelDuration - elapsed); 

        if (m_TimeLeft <= 0) {
            m_TimeLeft = 0;
            m_isTimerRunning = false;
            std::cout << "Time's up!" << std::endl;
        }
    }
}

std::string ToolbarGame::getTimeString() const {
    int totalSeconds = static_cast<int>(m_TimeLeft);
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream oss;
    oss << minutes << ":" << (seconds < 10 ? "0" : "") << seconds;
    return oss.str();
}

void ToolbarGame::setLevelDuration(const float duration) {
    m_LevelDuration = duration;
    m_TimeLeft = duration;
    m_isTimerRunning = true;  
    m_clock.restart();  
}

float ToolbarGame::getTimeLeft() const {
    return m_TimeLeft;
}

float ToolbarGame::getLevelDuration() const {
    return m_LevelDuration;
}

void ToolbarGame::setTimer(const float duration) {
    setLevelDuration(duration);
}

void ToolbarGame::ShowPresent(const char Present) {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    // Set the sprite texture based on the present type
    switch (Present) {
    case 'F':
        m_presentText.setTexture(resourceManager.getTexture("GuardFreeze.png"));
        break;
    case 'L':
        m_presentText.setTexture(resourceManager.getTexture("ExtraLife.png"));
        break;
    case 'R':
        m_presentText.setTexture(resourceManager.getTexture("RemoveGuard.png"));
        break;
    case 'T':
        m_presentText.setTexture(resourceManager.getTexture("ExtraTime.png"));
        break;
    default:
        return;  
    }

    m_presentText.setPosition(WINDOW_WIDTH / 2 - 55.f, 0.f);
    m_presentText.setScale(0.5f, 0.5f);
    m_presentClock.restart();
}

void ToolbarGame::updateTimerDisplay(const float deltaTime) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    UpdateTimer();
    sf::Text& timerText = resourceManager.getText("timer");
    timerText.setString(getTimeString());
    float timeLeft = getTimeLeft();

    // Heartbeat effect on the timer text (pulsing)
    if (timeLeft <= 10) { 
        float scaleFactor = 1.0f + 0.1f * sin(3.f * timeLeft);  
        m_timer.setScale(scaleFactor, scaleFactor); 
    }
    else {
        m_timer.setScale(1.f, 1.f); 
    }

    if (timeLeft > 30) {
        timerText.setFillColor(sf::Color(255, 255, 255, 255));  
        m_progressBar.setFillColor(sf::Color::Green);  
    }
    else if (timeLeft > 10) {
        timerText.setFillColor(sf::Color(255, 255, 255, 150));  
        m_progressBar.setFillColor(sf::Color::Yellow);  
    }
    else {
        timerText.setFillColor(sf::Color(255, 0, 0, 255));
        m_progressBar.setFillColor(sf::Color::Red);  
    }
    float rotationSpeed = 30.f * (1.f - (timeLeft / m_LevelDuration));
    timerText.setRotation(rotationSpeed * deltaTime);
    animateProgressBar(deltaTime);
    float heartscale = 0.2f * sin(1.f * timeLeft);  // Scaling based on time left
    float clockRotation = (15.0f - (timeLeft / m_LevelDuration)) * 22.f;  // Calculate rotation

    for (auto& heart : m_heart) {
       
        heart.setOrigin(
            heart.getGlobalBounds().width / 2,
            heart.getGlobalBounds().height / 2
        );
        heart.setScale(heartscale, heartscale);
        heart.setRotation(clockRotation);
    }

}

void ToolbarGame::animateProgressBar(const float deltaTime) {
    float timeLeft = getTimeLeft();
    float levelDuration = getLevelDuration();
    float targetWidth = 200.f * (timeLeft / levelDuration);
    float currentWidth = m_progressBar.getSize().x;
    float smoothTransition = currentWidth + (targetWidth - currentWidth) * deltaTime * 5.f;  // The factor "5.f" controls the smoothness
    m_progressBar.setSize(sf::Vector2f(smoothTransition, 10.f));
}

void ToolbarGame::handleMouseClick(const sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixelPosition);

    if (m_muteButton.getGlobalBounds().contains(mousePosition)) {
        std::cout << "Mute button clicked!" << std::endl;  
        toggleMute();
    }
}

void ToolbarGame::toggleMute() {
    m_isMuted = !m_isMuted;
    ResourceManager& resourceManager = ResourceManager::getInstance();
   
    m_muteButton.setTexture(m_isMuted ? resourceManager.getTexture("mute.png") : resourceManager.getTexture("unmute.png"));
    sf::Listener::setGlobalVolume(m_isMuted ? 0.0f : 100.0f); 
}

void ToolbarGame::startTimer() {
    m_isTimerRunning = true;
    m_clock.restart();
}

bool ToolbarGame::getIsTimerRunning() const {
	return m_isTimerRunning;
}

void ToolbarGame::pauseTimer() {
    if (!m_isPaused) {  
        m_isPaused = true;
        m_timePaused = getTimeLeft();
        sf::Listener::setGlobalVolume( 0.0f); // Mute all sounds in SFML
    }
}

void ToolbarGame::resumeTimer() {
    if (m_isPaused) {  
        m_isPaused = false;
		setTimer(m_timePaused);
        sf::Listener::setGlobalVolume(100.0f);
    }
}

void ToolbarGame::setLevel(int level) {
    m_levelText.setString("Level: " + std::to_string(level));
}

int ToolbarGame::getScore() {
    return m_score;
}
