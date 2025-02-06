#include "Present.h"
#include <iostream>

Present::Present() 
{
	ResourceManager& resourceManager = ResourceManager::getInstance();
	setTexture(resourceManager.getTexture("present.png"));
	m_numPresent++; // Increase count when created
}

int Present::m_numPresent = 0;

int Present::getPresentCount()
{
	return m_numPresent;
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
