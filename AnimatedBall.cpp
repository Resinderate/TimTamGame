#include "AnimatedBall.h"

AnimatedBall::AnimatedBall() :
	m_circle(15, 30),
	m_duration(0),
	m_over(false),
	m_endScale(),
	m_alphaReducePerFrame(0),
	m_scaleIncreasePerFrame()
{

}
AnimatedBall::AnimatedBall(const sf::Vector2f &p_position, sf::Color p_color) :
	m_circle(15, 30),
	m_duration(0.5),
	m_over(false),
	m_endScale(1.75, 1.75)
{
	m_circle.setPosition(p_position);
	m_circle.setFillColor(sf::Color::Transparent);
	m_circle.setOutlineThickness(5); //TBD
	m_circle.setOutlineColor(p_color);
	m_scaleIncreasePerFrame = (m_endScale - m_circle.getScale()) / (60 * m_duration);
	m_alphaReducePerFrame = m_circle.getOutlineColor().a / (60 * m_duration);
}

void AnimatedBall::update()
{
	m_circle.setScale(m_circle.getScale() + m_scaleIncreasePerFrame);
	sf::Color temp = m_circle.getOutlineColor();
	temp.a -= m_alphaReducePerFrame;
	m_circle.setOutlineColor(temp);

	if(m_circle.getScale().x > m_endScale.x || m_circle.getOutlineColor().a < 0)
		m_over = true;
}

bool AnimatedBall::isOver()
{
	return m_over;
}

sf::CircleShape AnimatedBall::getCircle()
{
	return m_circle;
}