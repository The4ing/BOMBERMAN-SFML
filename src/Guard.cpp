#include "Guard.h"


Guard::Guard() : m_previousPosition(0.f, 0.f), m_frameWidth(127.5f), m_frameHeight(163.3f),
m_animationFrame(0), m_freezeGuard(false)
{
	m_numGuard++;
}

int Guard::m_numGuard = 0;


int Guard::getGuardCount()
{
	return m_numGuard;
}

void Guard::restartNumGuard()
{
	m_numGuard = 0;
}

void Guard::reduceNumGuard()
{
	m_numGuard--;
}



void Guard::revertPosition()
{
	setPosition(m_previousPosition.x, m_previousPosition.y);
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

void Guard::setFreezeGaurd(const bool status)
{
	m_freezeGuard = status;
}

const bool Guard::getIsFreeze() const 
{
	return m_freezeGuard;
}



void Guard::draw(sf::RenderWindow& window) const
{
	
	window.draw(getSprite());
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







