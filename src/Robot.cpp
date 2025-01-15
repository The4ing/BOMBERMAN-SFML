//// Robot.cpp
//#include "Robot.h"
//
//Robot::Robot(const sf::Texture& texture, const sf::Vector2f& startPosition)
//    : m_direction(0.f, 0.f), m_speed(150.f) { // Speed in pixels per second
//    m_sprite.setTexture(texture);
//    m_sprite.setPosition(startPosition);
//}
//
//void Robot::handleInput(sf::Keyboard::Key key, bool isPressed) {
//    if (isPressed) {
//        switch (key) {
//        case sf::Keyboard::Up:    m_direction = { 0.f, -1.f }; break;
//        case sf::Keyboard::Down:  m_direction = { 0.f,  1.f }; break;
//        case sf::Keyboard::Left:  m_direction = { -1.f, 0.f }; break;
//        case sf::Keyboard::Right: m_direction = { 1.f, 0.f }; break;
//        default: break;
//        }
//    }
//    else {
//        m_direction = { 0.f, 0.f }; // Stop moving on key release
//    }
//}
//
//void Robot::update(float deltaTime) {
//    if (m_direction != sf::Vector2f(0.f, 0.f)) {
//        move(deltaTime);
//    }
//}
//
//void Robot::draw(sf::RenderWindow& window) {
//    window.draw(m_sprite);
//}
//
//void Robot::setBounds(const sf::FloatRect& bounds) {
//    m_bounds = bounds;
//}
//
//void Robot::move(float deltaTime) {
//    sf::Vector2f newPosition = m_sprite.getPosition() + m_direction * m_speed * deltaTime;
//
//    // Check bounds
//    if (newPosition.x < m_bounds.left ||
//        newPosition.x + m_sprite.getGlobalBounds().width > m_bounds.left + m_bounds.width ||
//        newPosition.y < m_bounds.top ||
//        newPosition.y + m_sprite.getGlobalBounds().height > m_bounds.top + m_bounds.height) {
//        return; // Prevent moving out of bounds
//    }
//
//    m_sprite.setPosition(newPosition);
//}
