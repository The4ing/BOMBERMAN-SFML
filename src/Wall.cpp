#include "Wall.h"

Wall::Wall(const sf::Texture& texture) {
    m_sprite.setTexture(texture); // Assign the texture to the sprite
}

char Wall::getSymbol() const {
    return '#'; // Represents the wall in the game
}

sf::Vector2f Wall::getPosition() const {
    return m_sprite.getPosition(); // Returns the sprite's current position
}

void Wall::setPosition(float x, float y) {
    m_sprite.setPosition(x, y); // Sets the sprite's position
}

void Wall::draw(sf::RenderWindow& window) const {
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





void Wall::collideWith(GameObject* other)
{
    other->collideWith(this);  // Double dispatch
}





void Wall::collideWith(Robot* robot)
{
    std::cout << "Wall collided with a robot!" << std::endl;
}



void Wall::collideWith(Guard* Guard)
{
    std::cout << "Wall collided with a Guard!" << std::endl;
}



