#include "Rock.h"

Rock::Rock(const sf::Texture& texture) {
    m_sprite.setTexture(texture); // Assign the texture to the sprite
}

char Rock::getSymbol() const {
    return '#'; // Represents the Rock in the game
}

sf::Vector2f Rock::getPosition() const {
    return m_sprite.getPosition(); // Returns the sprite's current position
}

void Rock::setPosition(float x, float y) {
    m_sprite.setPosition(x, y); // Sets the sprite's position
}

void Rock::draw(sf::RenderWindow& window) const {
    sf::Sprite sprite = m_sprite;

    float windowWidth = 1920.0f; // Example window width
    float windowHeight = 1080.0f; // Example window height
    float m_cellSizex = windowWidth / static_cast<float>(17);
    float m_cellSizey = windowHeight / static_cast<float>(9);

    sprite.setScale(
        m_cellSizex / sprite.getTexture()->getSize().x,
        m_cellSizey / sprite.getTexture()->getSize().y
    ); // Scale to fit cell size
    window.draw(sprite);
}







void Rock::collideWith(GameObject* other)
{
    other->collideWith(this);
}

void Rock::collideWith(Guard* Guard)
{
    std::cout << "Rock collided with a Guard!" << std::endl;
}

void Rock::collideWith(Robot* robot)
{
    std::cout << "Rock collided with a robot!" << std::endl;
}



