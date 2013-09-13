/*
	AnimatedBall.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef ANIMATEDBALL_H
#define ANIMATEDBALL_H

#include <SFML/Graphics.hpp>

class AnimatedBall
{
private:
	bool			m_over;
	float			m_duration;
	int				m_alphaReducePerFrame;
	sf::CircleShape m_circle;
	sf::Vector2f	m_endScale;
	sf::Vector2f	m_scaleIncreasePerFrame;

public:
	AnimatedBall();
	AnimatedBall(const sf::Vector2f &p_position, sf::Color p_color);
	sf::CircleShape getCircle();
	bool			isOver();
	void			update();
};
#endif //ANIMATEDBALL_H