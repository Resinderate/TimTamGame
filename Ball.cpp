/*
	Ball.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "Ball.h"

/*
	Name:	Default Constructor
	Desc:	Default Constructor for Ball
	Args:	None
	Rtrn:	None
*/
Ball::Ball() :
	m_circle(0, 0),
	m_velocity(),
	m_hue(0)
{

}

/*
	Name:	Constructor
	Desc:	Constructor for Ball
	Args:	p_pos,		the position of the ball
			p_velocity,	the velocity vector for the ball
			p_color,	the color of the ball
			p_hue,		the hue of the ball
	Rtrn:	None
*/
Ball::Ball(const sf::Vector2f &p_pos, const sf::Vector2f &p_velocity, const sf::Color &p_color, int p_hue) :
	m_circle(15, 30),
	m_velocity(p_velocity),
	m_hue(p_hue)
{
	m_circle.setPosition(p_pos.x, p_pos.y);
	m_circle.setFillColor(p_color);
	m_circle.setOrigin(15, 15);
}

/*
	Name:	Getters and Setters
	Desc:	A bunch of getters and setters for all the variables of the ball
	Args:	Various
	Rtrn:	Various
*/
void Ball::setPos(const sf::Vector2f &p_pos)
{
	m_circle.setPosition(p_pos);
}

void Ball::setVelocty(const sf::Vector2f &p_velocity)
{
	m_velocity = p_velocity;
}

void Ball::setColor(sf::Color p_color)
{
	m_circle.setFillColor(p_color);
}

void Ball::setHue(int p_hue)
{
	m_hue = p_hue;
}

sf::Vector2f Ball::getPosition()
{
	return m_circle.getPosition();
}

sf::Vector2f Ball::getVelocity()
{
	return m_velocity;
}

sf::Color Ball::getColor()
{
	return m_circle.getFillColor();
}

int Ball::getHue()
{
	return m_hue;
}

sf::CircleShape Ball::getCircle()
{
	return m_circle;
}

/*
	Name:	move
	Desc:	moves the ball by the amount found in the velocity vector
	Args:	None
	Rtrn:	None
*/
void Ball::move()
{
	m_circle.setPosition(m_circle.getPosition().x + m_velocity.x, m_circle.getPosition().y + m_velocity.y);
}