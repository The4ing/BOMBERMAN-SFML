#include "ToolbarGame.h"


ToolbarGame::ToolbarGame()
    : m_isTimerRunning(true), m_LevelDuration(0), m_TimeLeft(0),m_score(0), m_isMuted(false), m_num_heart(0){
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
    m_scoreText.setFont(resourceManager.getFont("digit.ttf")); // Use existing font
    m_scoreText.setCharacterSize(40);  // Set a good size
    m_scoreText.setOutlineThickness(3);
    m_scoreText.setStyle(sf::Text::Bold);
    m_scoreText.setFillColor(sf::Color::White);  // White text
    m_scoreText.setPosition(WINDOW_WIDTH / 2 - 50.f, 30.f); // Center horizontally
    m_scoreText.setString("Score: 0");  // Initial score




    // Set up timer sprite
    m_timer.setTexture(resourceManager.getTexture("timer.png"));
    m_timer.setOrigin(m_timer.getGlobalBounds().width / 2, m_timer.getGlobalBounds().height / 2);  // Set origin to center of the sprite
    m_timer.setPosition(105.f, 50.f);
    m_timer.setScale(0.4f, 0.4f);
   


    // Set up mute button

    m_muteButton.setTexture(resourceManager.getTexture("unmute.png"));
    m_muteButton.setScale(0.1f, 0.1f);
    m_muteButton.setPosition(1850.f, 10.f);
    
    m_heart.resize(NUM_HEART);  // Reserve space for 3 sprites

    // Set up heart sprites
    for (int i = 0; i < NUM_HEART; ++i) {
        std::string heartKey = "heart" + std::to_string(i);
        m_heart[i].setTexture(resourceManager.getTexture("heart.png"));
        m_heart[i].setOrigin(m_heart[i].getGlobalBounds().width / 2, m_heart[i].getGlobalBounds().height / 2);
        m_heart[i].setPosition(1750.f - i * 40.f, 50.f);
        m_heart[i].setScale(0.3f, 0.3f);
        m_num_heart++;
    }
}





//void ToolbarGame::LoudSprite() {
//
//    // Create the clock hand sprite
//
//
//    //m_clockHand.setTexture(GetTexture(CLOCK));
//    //SetSprite(m_clockHand, 400.f, 50.f, 0.2f);  // Center the clock on the screen
//
//
//    //// Create the arrow sprite
//    //m_arrow.setTexture(GetTexture(ARROW));
//    //SetSprite(m_arrow, m_clockHand.getPosition().x, m_clockHand.getPosition().y, 0.4f);  // Center the clock on the screen
//
//
//    //create timer picture
//    m_timer.setTexture(GetTexture(TIMER));
//    SetSprite(m_timer, m_timerText.getPosition().x, m_timerText.getPosition().y,0.2f);  // Center the clock on the screen
//  //  m_timer.setScale(m_timerText.getPosition().x, m_timerText.getPosition().y);
//
//
//    // Assuming you want an array of 3 sprites, each with a decreasing position
//    m_heart.resize(NUM_HEART);  // Reserve space for 3 sprites
//
//    int decrease = 1800;
//    for (int i = 0; i < NUM_HEART; ++i) {
//
//        m_heart[i].setTexture(GetTexture(HEART));  // Assign texture to sprite
//        SetSprite(m_heart[i], decrease, 50.f, 0.2f);  // Set position and scale
//        decrease -= 50;  // Decrease the position for the next sprite
//    }
//
//
//
//}



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
        m_num_heart--;  // Decrease heart count first
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
    window.draw(m_scoreText);  // Draw the score in the toolbar

    // Draw present text if it's been less than 2 seconds
    if (m_presentClock.getElapsedTime().asSeconds() < 2.0f) {
        window.draw(m_presentText);
    }
}




void ToolbarGame::IncreaseTime(const int extraTime) {
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Text& timerText = resourceManager.getText("timer");

    m_TimeLeft += extraTime;  // Directly modify the remaining time
    if (m_TimeLeft > MAX_TIME) {
        m_TimeLeft = MAX_TIME;  // Cap the time at the maximum allowed time
    }

    // Reset the clock to ensure correct countdown behavior
    m_clock.restart();
    m_LevelDuration = std::max(m_LevelDuration, m_TimeLeft);  // Ensure duration doesn't shrink

    // Immediately update the display
    timerText.setString(getTimeString());

    std::cout << "Time increased by " << extraTime << " seconds. New time: " << m_TimeLeft << "s\n";
}






//functions for timer
void ToolbarGame::UpdateTimer() {
    if (m_isTimerRunning) {
        sf::Time elapsed = m_clock.getElapsedTime();
        float newTime = m_LevelDuration - elapsed.asSeconds();

        if (newTime < m_TimeLeft) {  // Only reduce time, don't override increases
            m_TimeLeft = newTime;
        }

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
    m_isTimerRunning = true;  // Ensure the timer is running
    m_clock.restart();  // Restart the clock
}

// Get the time left for the level
float ToolbarGame::getTimeLeft() const {
    return m_TimeLeft;
}

// Get the total level duration
float ToolbarGame::getLevelDuration() const {
    return m_LevelDuration;
}
//void ToolbarGame::CallUpdateTimer() {
//    UpdateTimer();
//}

void ToolbarGame::setTimer(const float duration) {
    setLevelDuration(duration);
}

//void ToolbarGame::callUpdateToolbar(const float deltaTime)
//{
//    updateTimerDisplay(deltaTime);
//
//}



void ToolbarGame::ShowPresent(const char Present) {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    sf::Text presentText;
    presentText.setFont(resourceManager.getFont("digit.ttf"));
    presentText.setCharacterSize(35);
    presentText.setFillColor(sf::Color::White);
    presentText.setOutlineThickness(3);
    presentText.setOutlineColor(sf::Color::Black);
    presentText.setStyle(sf::Text::Bold);
    presentText.setPosition(WINDOW_WIDTH - 1550.f / 2 , 30.f); // Positioned next to the score

    // Set the message based on the present type
    switch (Present) {
    case 'F':
        presentText.setString("Guards frozen for 3 sec!");
        break;
    case 'L':
        presentText.setString("You got an extra life!");
        break;
    case 'R':
        presentText.setString("One guard removed!");
        break;
    case 'T':
        presentText.setString("You got an extra 30 sec!");
        break;
    default:
        return;  // No valid present, exit function
    }

    // Draw the text in the existing draw function
    m_presentText = presentText; // Store text so it's drawn in ToolbarGame::draw()

    // Start a timer so it disappears after some time
    m_presentClock.restart();
}



void ToolbarGame::updateTimerDisplay(const float deltaTime) {
    // Update the timer first (call your UpdateTimer() method)
    ResourceManager& resourceManager = ResourceManager::getInstance();

    UpdateTimer();

    sf::Text& timerText = resourceManager.getText("timer");
    timerText.setString(getTimeString());

    // Get the time left
    float timeLeft = getTimeLeft();

    // Heartbeat effect on the timer text (pulsing)
    if (timeLeft <= 10) { // Apply heartbeat effect only when time is low
        float scaleFactor = 1.0f + 0.1f * sin(3.f * timeLeft);  // Sinusoidal pulse effect
        m_timer.setScale(scaleFactor, scaleFactor);  // Scale the text
    }
    else {
        m_timer.setScale(1.f, 1.f);  // Reset scale when time is not critical
    }

    // Fading Text Effect & Change Progress Bar Color
    if (timeLeft > 30) {
        timerText.setFillColor(sf::Color(255, 255, 255, 255));  // Full opacity for fading effect
        m_progressBar.setFillColor(sf::Color::Green);  // Progress bar green
    }
    else if (timeLeft > 10) {
        timerText.setFillColor(sf::Color(255, 255, 255, 150));  // Slightly faded text
        m_progressBar.setFillColor(sf::Color::Yellow);  // Progress bar yellow
    }
    else {
        timerText.setFillColor(sf::Color(255, 0, 0, 255));  // Red text for urgency
        m_progressBar.setFillColor(sf::Color::Red);  // Progress bar red
    }

    // Rotation Effect: Rotate the timer text as the time gets closer to 0
    float rotationSpeed = 30.f * (1.f - (timeLeft / m_LevelDuration));  // Increase speed as time runs out
    timerText.setRotation(rotationSpeed * deltaTime);

    // Smoothly animate the progress bar based on time left
    animateProgressBar(deltaTime);

    // Update the rotation of the clock hand (robot texture)
   // float clockRotation = (1.0f - (timeLeft / m_LevelDuration)) * 360.f;  // Rotate based on time remaining
   // m_arrow.setRotation(clockRotation);  // Apply the calculated rotation to the clock hand

    float heartscale = 0.2f * sin(1.f * timeLeft);  // Scaling based on time left
    float clockRotation = (15.0f - (timeLeft / m_LevelDuration)) * 22.f;  // Calculate rotation


    for (auto& heart : m_heart) {
       
        heart.setOrigin(
            heart.getGlobalBounds().width / 2,
            heart.getGlobalBounds().height / 2
        );

        // Set position and scale
        heart.setScale(heartscale, heartscale);

        // Apply rotation
        heart.setRotation(clockRotation);


    }

}


void ToolbarGame::animateProgressBar(const float deltaTime) {
    float timeLeft = getTimeLeft();
    float levelDuration = getLevelDuration();

    // Calculate the target width based on remaining time
    float targetWidth = 200.f * (timeLeft / levelDuration);
    float currentWidth = m_progressBar.getSize().x;

    // Smooth transition of width change
    float smoothTransition = currentWidth + (targetWidth - currentWidth) * deltaTime * 5.f;  // The factor "5.f" controls the smoothness
    m_progressBar.setSize(sf::Vector2f(smoothTransition, 10.f));
}

void ToolbarGame::handleMouseClick(const sf::RenderWindow& window, const sf::Vector2i& mousePixelPosition) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixelPosition);

    if (m_muteButton.getGlobalBounds().contains(mousePosition)) {
        std::cout << "Mute button clicked!" << std::endl;  // Debug check
        toggleMute();
    }
}



void ToolbarGame::toggleMute() {
    m_isMuted = !m_isMuted;
    ResourceManager& resourceManager = ResourceManager::getInstance();
   
    m_muteButton.setTexture(m_isMuted ? resourceManager.getTexture("mute.png") : resourceManager.getTexture("unmute.png"));
    std::cout << (m_isMuted ? "Muted!" : "Unmuted!") << std::endl;
    // Apply mute/unmute effect
    sf::Listener::setGlobalVolume(m_isMuted ? 0.0f : 100.0f); // Mute all sounds in SFML
}

void ToolbarGame::startTimer() {
    m_isTimerRunning = true;
    m_clock.restart();
  //  m_TimeLeft = m_LevelDuration;  // Reset time left
}

bool ToolbarGame::getIsTimerRunning() const {
	return m_isTimerRunning;
}
