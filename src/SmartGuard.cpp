#include "SmartGuard.h"


SmartGuard::SmartGuard() {


}


void SmartGuard::setPosition(float newX, float newY) {
	m_sprite.setPosition(x, y);
}

void SmartGuard::update(float deltaTime) {
  


}

void SmartGuard::draw(sf::RenderWindow& window) const  {
	window.draw(m_sprite);
}

void SmartGuard::handleInput(sf::Keyboard::Key key, bool isPressed) {
  



}

void SmartGuard::setVelocity(float vx, float vy) {


}




sf::Vector2f SmartGuard::getPosition() const
{
	return m_sprite.getPosition();
}
