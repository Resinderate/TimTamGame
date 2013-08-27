#include "Ball.h"

Ball::Ball() :
	m_circle(0, 0),
	m_xVelocity(0),
	m_yVelocity(0),
	m_hue(0)
{

}

Ball::Ball(float p_x, float p_y, float p_xVelocity, float p_yVelocity, sf::Color p_color, int p_hue) :
	m_circle(15, 30),			//PLACEHOLDER VALUES
	m_xVelocity(p_xVelocity),
	m_yVelocity(p_yVelocity),
	m_hue(p_hue)
{
	m_circle.setPosition(p_x, p_y);
	m_circle.setFillColor(p_color);
	m_circle.setOrigin(15, 15);    //USING THE PLACEHOLDER ABOVE
}

void Ball::setPos(float p_x, float p_y)
{
	m_circle.setPosition(p_x, p_y);
}

void Ball::setXVel(float p_xVel)
{
	m_xVelocity = p_xVel;
}

void Ball::setYVel(float p_yVel)
{
	m_yVelocity = p_yVel;
}

void Ball::setColor(sf::Color p_color)
{
	m_circle.setFillColor(p_color);
}

void Ball::setHue(int p_hue)
{
	m_hue = p_hue;
}

float Ball::getX()
{
	return m_circle.getPosition().x;
}

float Ball::getY()
{
	return m_circle.getPosition().y;
}

float Ball::getXVel()
{
	return m_xVelocity;
}

float Ball::getYVel()
{
	return m_yVelocity;
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

void Ball::Move()
{
	m_circle.setPosition(m_circle.getPosition().x + m_xVelocity, m_circle.getPosition().y + m_yVelocity);
}