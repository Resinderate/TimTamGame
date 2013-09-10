#include "Player.h"

Player::Player(float p_x, float p_y, const sf::Color &p_color) :
	m_circle(15, 40), //Hard coded, figure these out.
	m_points(0),
	m_multiplier(1),
	m_lastX(p_x),
	m_lastY(p_y),
	m_particleSys(p_color, sf::Vector2f(p_x, p_y), sf::Vector2f(-3, 3), 30, m_circle.getRadius(), 1000)
{
	m_circle.setPosition(p_x, p_y);
	m_circle.setFillColor(p_color);
	m_circle.setOrigin(15, 15);
}

void Player::setCircle(sf::CircleShape p_circle)
{
	m_circle = p_circle;
}

void Player::setPosition(float p_x, float p_y)
{
	m_circle.setPosition(p_x, p_y);
}

void Player::setLastX(float p_lastX)
{
	m_lastX = p_lastX;
}

void Player::setLastY(float p_lastY)
{
	m_lastY = p_lastY;
}

void Player::setMultiplier(int p_multiplier)
{
	m_multiplier = p_multiplier;
}

void Player::addPoints(int p_points)
{
	m_points += p_points * m_multiplier;
}

sf::CircleShape Player::getCircle()
{
	return m_circle;
}

float Player::getX()
{
	return m_circle.getPosition().x;
}

float Player::getY()
{
	return m_circle.getPosition().y;
}

float Player::getLastX()
{
	return m_lastX;
}

float Player::getLastY()
{
	return m_lastY;
}

int Player::getMultiplier()
{
	return m_multiplier;
}

void Player::resetPoints()
{
	m_points = 0;
}

int Player::getPoints()
{
	return m_points;
}

ParticleSys& Player::getParticleSys()
{
	return m_particleSys;
}
