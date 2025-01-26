#include "Door.h"

Door::Door(const sf::Texture& texture) {
    m_sprite.setTexture(texture); // Assign the texture to the sprite
}

char Door::getSymbol() const {
    return 'D'; // Represents the Door in the game
}

sf::Vector2f Door::getPosition() const {
    return m_sprite.getPosition(); // Returns the sprite's current position
}

void Door::setPosition(float x, float y) {
    m_sprite.setPosition(x, y); // Sets the sprite's position
}

void Door::draw(sf::RenderWindow& window) const {
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



void Door::collideWith(GameObject* other)
{
    other->collideWith(this);  // Double dispatch
}




void Door::collideWith(Robot* robot)
{
    std::cout << "Door collided with a robot!" << std::endl;
}

void Door::collideWith(Bomb* bomb)
{
    std::cout << "Door collided with a bomb!" << std::endl;
}


void Door::collideWith(Guard* Guard)
{
    std::cout << "Door collided with a Guard!" << std::endl;
}