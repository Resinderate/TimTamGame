/*
	Player.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "ParticleSys.h"

class Player
{
private:
	int				m_multiplier;
	int				m_points;
	ParticleSys		m_particleSys;
	sf::CircleShape m_circle;
	sf::Vector2f	m_lastPos;
	
public:
	Player(sf::Vector2f p_pos, const sf::Color &p_color);
	int				getMultiplier();
	int				getPoints();
	ParticleSys&	getParticleSys();
	sf::CircleShape getCircle();
	sf::Vector2f	getLastPos();
	sf::Vector2f	getPos();
	void			addPoints(int p_points);
	void			resetPoints();
	void			setCircle(sf::CircleShape p_circle);
	void			setLastPosition(sf::Vector2f p_lastPos);
	void			setMultiplier(int p_multiplier);
	void			setPosition(float p_x, float p_y);
};
#endif