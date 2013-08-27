#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::CircleShape m_circle;
	float m_xVelocity;
	float m_yVelocity;
	int m_hue;
	
public:
	Ball();
	Ball(float p_x, float p_y, float p_xVelocity, float p_yVelocity, sf::Color p_color, int p_hue);
	void setPos(float p_x, float p_y);
	void setXVel(float p_xVel);
	void setYVel(float p_yVel);
	void setColor(sf::Color p_color);
	void setHue(int p_hue);
	float getX();
	float getY();
	float getXVel();
	float getYVel();
	sf::Color getColor();
	int getHue();
	sf::CircleShape getCircle();
	void Move();
};
#endif