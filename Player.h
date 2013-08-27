#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player
{
private:
	sf::CircleShape m_circle;
	int m_points;
	int m_multiplier;
	//These represent where the player was on the last frame. Used to calculate some part of the points.
	float m_lastX;
	float m_lastY;
	//PlayerParticleSys m_particleSys;
	
public:
	Player(float p_x, float p_y, const sf::Color &p_color);
	void setCircle(sf::CircleShape p_circle);
	void setPosition(float p_x, float p_y);
	void setLastX(float p_lastX);
	void setLastY(float p_lastY);
	void setMultiplier(int p_multiplier);
	void addPoints(int p_points);
	sf::CircleShape getCircle();
	float getX();
	float getY();
	float getLastX();
	float getLastY();
	int getMultiplier();
	void resetPoints();
	int getPoints();
	

};
#endif