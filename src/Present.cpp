#include "Present.h"
#include <iostream>



Present::Present() 
{
	ResourceManager& resourceManager = ResourceManager::getInstance();
	setTexture(resourceManager.getTexture("present.png"));
	m_numPresent++; // Increase count when created
}

int Present::m_numPresent = 0;


//sf::Vector2f Present::getPosition() const
//{
//	return m_position;
//}

int Present::getPresentCount()
{
	return m_numPresent;
}


void Present::addNumPresent()
{
	m_numPresent++;
}

void Present::restartNumPresent()
{
	m_numPresent = 0;
}

void Present::reduceNumPresent()
{
	if (m_numPresent > 0) m_numPresent--;
}






void Present::draw(sf::RenderWindow& window) const
{
	window.draw(getSprite());
}







void Present::handleCollision(GameObject& other)
{
	other.handleCollisionWith(*this);
}

void Present::handleCollisionWith(Robot& robot)
{
	reduceNumPresent();
}






