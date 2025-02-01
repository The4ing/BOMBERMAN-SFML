#include "Guard.h"




Guard::Guard() : m_previousPosition(0.f, 0.f),m_frameWidth(127.5f), m_frameHeight(163.3f),\
m_animationFrame(0)

{}



void Guard::revertPosition()
{
	m_sprite.setPosition(m_previousPosition);
}



void Guard::setStartingPosition(float newX, float newY)
{
	m_startingPosition.x = newX;
	m_startingPosition.y = newY;
}

sf::Vector2f Guard::getStartingPosition()
{
	return m_startingPosition;
}

char Guard::getSymbol() const
{
	 return '!'; 
	
}

void Guard::setPosition(float newX, float newY)
{
	m_sprite.setPosition(newX, newY);

}


sf::Vector2f Guard::getPosition() const
{
	return m_sprite.getPosition();
}

sf::FloatRect Guard::getBoundingBox() const
{
	return m_sprite.getGlobalBounds();
}

void Guard::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
	sf::CircleShape collisionShape = getCollisionShape();
	collisionShape.setFillColor(sf::Color::Transparent);
	collisionShape.setOutlineColor(sf::Color::Red);
	collisionShape.setOutlineThickness(1.f);
	window.draw(collisionShape);
	
}


void Guard::handleCollision(GameObject& other)
{
	
	other.handleCollisionWith(*this);
	
}

void Guard::handleCollisionWith(Rock&)
{
	revertPosition();
}

void Guard::handleCollisionWith(Door&)
{
	revertPosition();
}

void Guard::setScale(float scaleX, float scaleY)
{
	m_sprite.setScale(scaleX, scaleY);
}





