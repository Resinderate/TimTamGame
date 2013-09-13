/*
	Player.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "Player.h"

/*
	Name:	Constructor
	Desc:	Constructor for Player
	Args:	p_pos,	the innitial position of the player
	Rtrn:	None
*/
Player::Player(sf::Vector2f p_pos, const sf::Color &p_color) :
	m_circle(15, 40),
	m_points(0),
	m_multiplier(1),
	m_lastPos(),
	m_particleSys(p_color, sf::Vector2f(p_pos), sf::Vector2f(-3, 3), 30, m_circle.getRadius(), 1000)
{
	m_circle.setPosition(p_pos);
	m_circle.setFillColor(p_color);
	m_circle.setOrigin(15, 15);
}

/*
	Name:	Getters and Setters
	Desc:	Getters and Setters for the variables in the player obj
	Args:	Various
	Rtrn:	Various
*/
void Player::setCircle(sf::CircleShape p_circle)
{
	m_circle = p_circle;
}

void Player::setPosition(float p_x, float p_y)
{
	m_circle.setPosition(p_x, p_y);
}

void Player::setLastPosition(sf::Vector2f p_lastPos)
{
	m_lastPos = p_lastPos;
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

sf::Vector2f Player::getPos()
{
	return m_circle.getPosition();
}

sf::Vector2f Player::getLastPos()
{
	return m_lastPos;
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
