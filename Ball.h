/*
	Ball.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::CircleShape m_circle;
	int				m_hue;
	sf::Vector2f	m_velocity;
	
public:
	Ball();
	Ball(const sf::Vector2f &p_pos, const sf::Vector2f &p_velocity, const sf::Color &p_color, int p_hue);
	sf::Vector2f	getPosition();
	sf::Vector2f	getVelocity();
	sf::Color		getColor();
	int				getHue();
	sf::CircleShape getCircle();
	void			move();
	void			setPos(const sf::Vector2f &p_pos);
	void			setVelocty(const sf::Vector2f &p_velocity);
	void			setColor(sf::Color p_color);
	void			setHue(int p_hue);
};
#endif