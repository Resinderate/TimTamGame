/*
	AnimatedBall.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "AnimatedBall.h"

/*
	Name:	Constructor
	Desc:	Default Constructor for AnimatedBall
	Args:	None
	Rtrn:	None
*/
AnimatedBall::AnimatedBall() :
	m_circle(15, 30),
	m_duration(0),
	m_over(false),
	m_endScale(),
	m_alphaReducePerFrame(0),
	m_scaleIncreasePerFrame()
{

}

/*
	Name:	Constructor
	Desc:	Constructor for AnimatedBall
	Args:	p_position, the position of the animation
			p_color,	the color of the ani
	Rtrn:	None
*/
AnimatedBall::AnimatedBall(const sf::Vector2f &p_position, sf::Color p_color) :
	m_circle(15, 30),
	m_duration(0.5),
	m_over(false),
	m_endScale(1.75, 1.75)
{
	m_circle.setPosition(p_position);
	m_circle.setFillColor(sf::Color::Transparent);
	m_circle.setOutlineThickness(5);
	m_circle.setOutlineColor(p_color);
	m_scaleIncreasePerFrame = (m_endScale - m_circle.getScale()) / (60 * m_duration);
	m_alphaReducePerFrame = m_circle.getOutlineColor().a / (60 * m_duration);
}

/*
	Name:	update
	Desc:	processes the animation of the ball
	Args:	None
	Rtrn:	None
*/
void AnimatedBall::update()
{
	m_circle.setScale(m_circle.getScale() + m_scaleIncreasePerFrame);
	sf::Color temp = m_circle.getOutlineColor();
	temp.a -= m_alphaReducePerFrame;
	m_circle.setOutlineColor(temp);

	if(m_circle.getScale().x > m_endScale.x || m_circle.getOutlineColor().a < 0)
		m_over = true;
}

/*
	Name:	isOver
	Desc:	getter for m_over
	Args:	None
	Rtrn:	m_over
*/
bool AnimatedBall::isOver()
{
	return m_over;
}

/*
	Name:	getCicle
	Desc:	getter for m_circle
	Args:	None
	Rtrn:	m_circle
*/
sf::CircleShape AnimatedBall::getCircle()
{
	return m_circle;
}