#include "ToolbarGame.h"



ToolbarGame::ToolbarGame()
    : m_isTimerRunning(false), m_LevelDuration(0), m_TimeLeft(0), m_isMuted(false){

    m_clock.restart();
    setLevelDuration(40);

    // Load font for timer text
    if (!m_font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error: Failed to load font!" << std::endl;
        return;
    }

    m_timerText.setFont(m_font);
    m_timerText.setCharacterSize(40);
    m_timerText.setFillColor(sf::Color::Green);
    m_timerText.setPosition(10.f, 10.f);

    // Load toolbar textures
    loadTextures();
    LoudSprite();

    // Load mute and unmute button textures
    if (!m_muteTexture.loadFromFile("mute.png") || !m_unmuteTexture.loadFromFile("unmute.png")) {
        std::cerr << "Error: Could not load mute/unmute textures!" << std::endl;
    }

    // Initialize mute button
    m_muteButton.setTexture(m_unmuteTexture);          // Default to unmuted
    m_muteButton.setScale(0.1f, 0.1f);                 // Scale down for smaller size
    m_muteButton.setPosition(1850.f, 10.f);            // Position at top-right of 1920x1080 screen
}




void ToolbarGame::LoudSprite() {

    // Create the clock hand sprite

     
    m_clockHand.setTexture(GetTexture(CLOCK));
    SetSprite(m_clockHand, 400.f, 50.f, 0.2f);  // Center the clock on the screen


    // Create the arrow sprite
    m_arrow.setTexture(GetTexture(ARROW));
    SetSprite(m_arrow, m_clockHand.getPosition().x, m_clockHand.getPosition().y, 0.4f);  // Center the clock on the screen


    // Assuming you want an array of 3 sprites, each with a decreasing position
    m_heart.resize(NUM_HEART);  // Reserve space for 3 sprites

    int decrease = 1800;
    for (int i = 0; i < NUM_HEART; ++i) {
       
        m_heart[i].setTexture(GetTexture(HEART));  // Assign texture to sprite
        SetSprite(m_heart[i], decrease, 50.f, 0.2f);  // Set position and scale
        decrease -= 200;  // Decrease the position for the next sprite
    }



}

void ToolbarGame::loadTextures() {
    m_ToolbatTexture.resize(SIZE_TOOLBAR);
    const std::map<int, std::string> textureFiles = {
       { HEART, "heart.png" },
       { CLOCK,"Clock.png" },
        { ARROW, "arrow.png" }
    };

    for (const auto& [index, filename] : textureFiles) {
        //std::cout << index << std::endl;
        if (!m_ToolbatTexture[index].loadFromFile(filename)) {
            std::cerr << "Error: Could not load texture file " << filename << std::endl;
        }
    }
}


const sf::Texture& ToolbarGame::GetTexture(const int& choice) const
{
    return m_ToolbatTexture[choice];
}

const int ToolbarGame::getHeartCount()
{
    return m_heart.size();
}

void ToolbarGame::draw(sf::RenderWindow& window) {
    for (const auto& heart : m_heart) {
        window.draw(heart);
    }
    window.draw(m_clockHand);
    window.draw(m_arrow);
    window.draw(m_progressBar);
    window.draw(m_timerText);
    window.draw(m_muteButton); // Draw the mute button
}

void ToolbarGame::SetSprite(sf::Sprite& picture, const float POSx, const float POSy, const float thicknes) const {
    picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);  // Set origin to center of the sprite
    picture.setPosition(POSx, POSy);  // Positioning the clock hand (adjust position as needed)
    picture.setScale(thicknes, thicknes);  // Uniform scaling for both axes (width and height)
}


void ToolbarGame::IncreaseTime(const int extraTime) {
    m_LevelDuration += extraTime;  // Add extra time
    //if (m_TimeLeft > m_LevelDuration) {
    //     m_LevelDuration = m_TimeLeft;  // Cap the time at the level duration
    //}
    std::cout << "Time increased by " << extraTime << " seconds." << std::endl;
   // while (1);
}




//functions for timer
void ToolbarGame::UpdateTimer() {
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

std::string ToolbarGame::getTimeString() const {
    int minutes = static_cast<int>(m_TimeLeft) / 60;
    int seconds = static_cast<int>(m_TimeLeft) % 60;
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


    CallUpdateTimer();

    m_timerText.setString("Time Left: " + getTimeString());

    // Get the time left
    float timeLeft = getTimeLeft();

    // Heartbeat effect on the timer text (pulsing)
    if (timeLeft <= 10) { // Apply heartbeat effect only when time is low
        float scaleFactor = 1.0f + 0.1f * sin(3.f * timeLeft);  // Sinusoidal pulse effect
        m_timerText.setScale(scaleFactor, scaleFactor);  // Scale the text
    }
    else {
        m_timerText.setScale(1.f, 1.f);  // Reset scale when time is not critical
    }

    // Fading Text Effect & Change Progress Bar Color
    if (timeLeft > 30) {
        m_timerText.setFillColor(sf::Color(255, 255, 255, 255));  // Full opacity for fading effect
        m_progressBar.setFillColor(sf::Color::Green);  // Progress bar green
    }
    else if (timeLeft > 10) {
        m_timerText.setFillColor(sf::Color(255, 255, 255, 150));  // Slightly faded text
        m_progressBar.setFillColor(sf::Color::Yellow);  // Progress bar yellow
    }
    else {
        m_timerText.setFillColor(sf::Color(255, 0, 0, 255));  // Red text for urgency
        m_progressBar.setFillColor(sf::Color::Red);  // Progress bar red
    }

    // Rotation Effect: Rotate the timer text as the time gets closer to 0
    float rotationSpeed = 30.f * (1.f - (timeLeft / m_LevelDuration));  // Increase speed as time runs out
    m_timerText.setRotation(rotationSpeed * deltaTime);

    // Smoothly animate the progress bar based on time left
    animateProgressBar(deltaTime);

    // Update the rotation of the clock hand (robot texture)
    float clockRotation = (1.0f - (timeLeft / m_LevelDuration)) * 360.f;  // Rotate based on time remaining
    m_arrow.setRotation(clockRotation);  // Apply the calculated rotation to the clock hand

    float heartscale = 0.3f * sin(3.f * timeLeft);  // Scaling based on time left
    clockRotation = (1.0f - (timeLeft / m_LevelDuration)) * 22.f;  // Calculate rotation

    for (int pos = 0; pos < m_heart.size(); pos++) {
      // Set the origin to the center of the sprite
      m_heart[pos].setOrigin(
           m_heart[pos].getGlobalBounds().width / 2,
           m_heart[pos].getGlobalBounds().height / 2
       );

        // Set position and scale
        m_heart[pos].setScale(heartscale, heartscale);

       // Apply rotation
        m_heart[pos].setRotation(clockRotation);
    }
}


void ToolbarGame::animateProgressBar(const float deltaTime)  {
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
    // Convert screen-space mouse position to world-space
    sf::Vector2f mousePosition = window.mapPixelToCoords(mousePixelPosition);

    // Check if the mouse click intersects with the mute button
    if (m_muteButton.getGlobalBounds().contains(mousePosition)) {
        toggleMute();
    }
}


void ToolbarGame::toggleMute() {
    m_isMuted = !m_isMuted; // Toggle mute state

    // Update the button texture based on the current state
    if (m_isMuted) {
        m_muteButton.setTexture(m_muteTexture);
        std::cout << "Muted!" << std::endl;
    }
    else {
        m_muteButton.setTexture(m_unmuteTexture);
        std::cout << "Unmuted!" << std::endl;
    }
}

void ToolbarGame::startTimer() {
    m_isTimerRunning = true;  // Start the timer
    m_clock.restart();        // Reset clock
}
