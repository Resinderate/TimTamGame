/*
	ParticleSys.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "ColorUtil.h"

//#define _USE_MATH_DEFINES
//#include <math.h>

class ParticleSys
{
private:
	int					m_duration;
	int					m_spreadRadius;
	sf::Color			m_emitterColor;
	sf::Vector2f		m_emitterPos;
	sf::Vector2f		m_movementVec;
	sf::VertexArray		m_verts;
	std::vector<int>	m_durations;
	
	void resetParticle(int p_particleIndex);

public:
	ParticleSys(sf::Color p_color, sf::Vector2f p_position, sf::Vector2f p_movementVec, int p_duration,
		int p_spreadRadius, int p_numParticles);
	sf::VertexArray&	getVerts();
	void				processParticles();
	void				moveEmitter(const sf::Vector2f &p_vec);
	void				setColor(sf::Color p_color);
};
#endif