#include "GameObject.h"

sf::Vector2f GameObject::getPosition() const
{
	return  m_sprite.getPosition();
}

void GameObject::setPosition(float newX, float newY)
{
	m_sprite.setPosition(newX, newY);
}

sf::FloatRect GameObject::getBoundingBox() const
{
	return m_sprite.getGlobalBounds();
}
void GameObject::setScale(float scaleX, float scaleY)
{
	m_sprite.setScale(scaleX, scaleY);
}

void GameObject::setTexture(const sf::Texture& texture) {

	m_sprite.setTexture(texture);


}

sf::Sprite& GameObject::getSprite()
{
	return m_sprite;
		
}

const sf::Sprite& GameObject::getSprite() const
{
	return m_sprite;
}






