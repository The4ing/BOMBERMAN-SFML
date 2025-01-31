#include "Present.h"
#include <iostream>



Present::Present() :m_activePresent(false)
{
	ResourceManager& resourceManager = ResourceManager::getInstance();
	m_sprite.setTexture(resourceManager.getTexture("present.png"));
	m_numPresent++; // Increase count when created
}

int Present::m_numPresent = 0;



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


sf::Vector2f Present::getPosition() const
{
	return m_position;
}

void Present::setPosition(float newX, float newY)
{
	m_position = { newX, newY };
	m_sprite.setPosition(m_position);
}

void Present::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::FloatRect Present::getBoundingBox() const
{
	return m_sprite.getGlobalBounds();
}

void Present::setActive()
{
	m_activePresent = true;
}

const bool Present::checkActive()
{
	return m_activePresent;
}

void Present::setScale(float scaleX, float scaleY)
{
	m_sprite.setScale(scaleX, scaleY);
}

void Present::handleCollision(GameObject& other)
{
	other.handleCollisionWith(*this);
}

void Present::handleCollisionWith(Robot& robot)
{
	setActive();
}






