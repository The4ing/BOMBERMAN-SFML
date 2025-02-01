#include "ToolbarGame.h"


ToolbarGame::ToolbarGame()
    : m_isTimerRunning(true), m_LevelDuration(0), m_TimeLeft(0), m_isMuted(false), m_num_heart(0){
    m_clock.restart();
    setTimer(40);

    ResourceManager& resourceManager = ResourceManager::getInstance();


    // Set up timer text
    sf::Text timerText;
    timerText.setFont(resourceManager.getFont("digit.ttf"));
    timerText.setCharacterSize(30);
    timerText.setOutlineThickness(4);
    timerText.setStyle(sf::Text::Bold);
    timerText.setPosition(80.f, 32.f);
    timerText.setScale(1.5f, 1.f);
    timerText.setLetterSpacing(2.f);
    resourceManager.addText("timer", timerText);

    // Set up timer sprite
    sf::Sprite timerSprite;
    timerSprite.setTexture(resourceManager.getTexture("timer.png"));
    timerSprite.setOrigin(timerSprite.getGlobalBounds().width / 2, timerSprite.getGlobalBounds().height / 2);  // Set origin to center of the sprite
    timerSprite.setPosition(100.f, 50.f);
    timerSprite.setScale(0.2f, 0.2f);
    resourceManager.addSprite("timer", timerSprite);


    // Set up mute button
    sf::Sprite muteButton;
    muteButton.setTexture(resourceManager.getTexture("unmute.png"));
    muteButton.setScale(0.1f, 0.1f);
    muteButton.setPosition(1850.f, 10.f);
    resourceManager.addSprite("mute", muteButton);

    // Set up heart sprites
    for (int i = 0; i < NUM_HEART; ++i) {
        std::string heartKey = "heart" + std::to_string(i);
        sf::Sprite heart;
        heart.setTexture(resourceManager.getTexture("heart.png"));
        heart.setOrigin(heart.getGlobalBounds().width / 2, heart.getGlobalBounds().height / 2);
        heart.setPosition(1750.f - i * 40.f, 50.f);
        heart.setScale(0.3f, 0.3f);
        resourceManager.addSprite(heartKey, heart);
        m_num_heart++;
    }
}
//ToolbarGame::ToolbarGame()
//    : m_isTimerRunning(true), m_LevelDuration(0), m_TimeLeft(0), m_isMuted(false) {
//    m_clock.restart();
//    setLevelDuration(40);
//
//    // Load font for timer text
//    if (!m_font.loadFromFile("digit.ttf")) {
//        std::cerr << "Error: Failed to load font!" << std::endl;
//        return;
//    }
//
//
//    m_timerText.setFont(m_font);
//    m_timerText.setCharacterSize(30);
//    m_timerText.setOutlineThickness(4);
//    m_timerText.setStyle(sf::Text::Bold);
//    m_timerText.setPosition(80.f, 32.f);
//    m_timerText.setScale(1.5f, 1.f);
//    m_timerText.setLetterSpacing(2.f);
//
//
//
//
//    // Load toolbar textures
//    loadTextures();
//    LoudSprite();
//
//    // Load mute and unmute button textures
//    if (!m_muteTexture.loadFromFile("mute.png") || !m_unmuteTexture.loadFromFile("unmute.png")) {
//        std::cerr << "Error: Could not load mute/unmute textures!" << std::endl;
//    }
//
//    // Initialize mute button
//    m_muteButton.setTexture(m_unmuteTexture);          // Default to unmuted
//    m_muteButton.setScale(0.1f, 0.1f);                 // Scale down for smaller size
//    m_muteButton.setPosition(1850.f, 10.f);            // Position at top-right of 1920x1080 screen
//}




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

//void ToolbarGame::LoudSprite() {
//    // Set the texture for the timer and position it at the center of the toolbar
//    m_timer.setTexture(GetTexture(TIMER));
//
//    // Center the timer on the top-left corner or another specific position
//    float timerX = 100.f;  // Adjust X coordinate for timer
//    float timerY = 50.f;   // Adjust Y coordinate for timer
//    SetSprite(m_timer, timerX, timerY, 0.2f);  // Reduce scale factor to size the sprite
//
//
//    // Assuming you want an array of 3 heart sprites, each spaced equally
//    m_heart.resize(NUM_HEART);  // Reserve space for the number of hearts
//
//    // Position the hearts relative to the timer
//    float heartX = 1750.f;  // Initial X position for the hearts
//    float heartY = 50.f;   // Same Y position as the timer
//    float heartSpacing = 40.f;  // Spacing between each heart
//
//    for (int i = 0; i < NUM_HEART; ++i) {
//        m_heart[i].setTexture(GetTexture(HEART));  // Assign texture to each heart sprite
//        SetSprite(m_heart[i], heartX, heartY, 0.3f);  // Adjust scale and position
//        heartX -= heartSpacing;  // Increment X position for the next heart
//    }
//}
//
//
//void ToolbarGame::loadTextures() {
//    m_ToolbatTexture.resize(SIZE_TOOLBAR);
//    const std::map<int, std::string> textureFiles = {
//       { HEART, "heart.png" },
//        { TIMER,"timer.png" },
//        //{ ARROW, "arrow.png" }*/
//    };
//
//    for (const auto& [index, filename] : textureFiles) {
//        //std::cout << index << std::endl;
//        if (!m_ToolbatTexture[index].loadFromFile(filename)) {
//            std::cerr << "Error: Could not load texture file " << filename << std::endl;
//        }
//    }
//}


//const sf::Texture& ToolbarGame::GetTexture(const int& choice) const
//{
//    return m_ToolbatTexture[choice];
//}

const int ToolbarGame::getHeartCount() const 
{
    return m_num_heart;
}


void ToolbarGame::IncreaseHeart(const bool add) {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    if (getHeartCount() < 4 && add) {
        std::string heartKey = "heart" + std::to_string(getHeartCount());
        sf::Sprite newHeart;
        newHeart.setPosition(1750.f - getHeartCount() * 40.f, 50.f);
        newHeart.setScale(0.3f, 0.3f);
        resourceManager.addSprite(heartKey, newHeart);
        m_num_heart++;
    }
    else if (!add && getHeartCount() > 0) {  // Remove a heart
        m_num_heart--;  // Decrease heart count first
        std::string heartKey = "heart" + std::to_string(getHeartCount());
        std::cout << heartKey << std::endl;
        // Check if `ResourceManager` has a remove method
        resourceManager.removeSprite(heartKey);
    }

}

void ToolbarGame::draw(sf::RenderWindow& window) {
    ResourceManager& resourceManager = ResourceManager::getInstance();

    window.draw(resourceManager.getSprite("timer"));
    window.draw(resourceManager.getText("timer"));
    window.draw(resourceManager.getSprite("mute"));
    window.draw(m_progressBar);

    for (int i = 0; i < getHeartCount(); ++i) {
        window.draw(resourceManager.getSprite("heart" + std::to_string(i)));
    }
}

//void ToolbarGame::draw(sf::RenderWindow& window) {
//    for (const auto& heart : m_heart) {
//        window.draw(heart);
//    }
//    // window.draw(m_clockHand);
//     // window.draw(m_arrow);
//    window.draw(m_timer);
//    window.draw(m_progressBar);
//    window.draw(m_timerText);
//    window.draw(m_muteButton); // Draw the mute button
//}

//void ToolbarGame::SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const {
//
//    picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);  // Set origin to center of the sprite
//    picture.setPosition(POSx, POSy);  // Positioning the clock hand (adjust position as needed)
//    picture.setScale(thicknes, thicknes);  // Uniform scaling for both axes (width and height)
//}


void ToolbarGame::IncreaseTime(const int extraTime) {

    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Text& timerText = resourceManager.getText("timer");
    m_TimeLeft += extraTime;  // Add extra time
    if (m_TimeLeft > MAX_TIME) {
        m_TimeLeft = MAX_TIME;  // Cap the time at the maximum allowed time
    }

    // Reset the clock to ensure correct countdown behavior
    m_clock.restart();

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
void ToolbarGame::CallUpdateTimer() {
    UpdateTimer();
}

void ToolbarGame::setTimer(const float duration) {
    setLevelDuration(duration);
}

void ToolbarGame::callUpdateToolbar(const float deltaTime)
{
    updateTimerDisplay(deltaTime);

}





void ToolbarGame::updateTimerDisplay(const float deltaTime) {
    // Update the timer first (call your UpdateTimer() method)
    ResourceManager& resourceManager = ResourceManager::getInstance();


    CallUpdateTimer();

    sf::Text& timerText = resourceManager.getText("timer");
    timerText.setString(getTimeString());

    // Get the time left
    float timeLeft = getTimeLeft();

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

    for (int pos = 0; pos < getHeartCount(); pos++) {
        // Set the origin to the center of the sprite
        std::string heartKey = "heart" + std::to_string(pos);
        sf::Sprite& Heart = resourceManager.getSprite(heartKey);
        Heart.setOrigin(
            Heart.getGlobalBounds().width / 2,
            Heart.getGlobalBounds().height / 2
        );

        // Set position and scale
        Heart.setScale(heartscale, heartscale);

        // Apply rotation
        Heart.setRotation(clockRotation);
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
    if (ResourceManager::getInstance().getSprite("mute").getGlobalBounds().contains(mousePosition)) {
        toggleMute();
    }
}



void ToolbarGame::toggleMute() {
    m_isMuted = !m_isMuted;
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sprite& muteButton = resourceManager.getSprite("mute");

    muteButton.setTexture(m_isMuted ? resourceManager.getTexture("mute.png") : resourceManager.getTexture("unmute.png"));
    std::cout << (m_isMuted ? "Muted!" : "Unmuted!") << std::endl;
}

void ToolbarGame::startTimer() {
    m_isTimerRunning = true;  // Start the timer
    m_clock.restart();        // Reset clock
}
