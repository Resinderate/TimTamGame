#ifndef PARTICLESYS_H
#define PARTICLESYS_H

#include "SFML/Graphics.hpp"
#include <vector>
#include "ColorUtil.h"

#define _USE_MATH_DEFINES
#include <math.h>

class ParticleSys
{
private:
	sf::Vector2f m_emitterPos;
	sf::Color m_emitterColor;
	int m_duration;
	sf::Vector2f m_movementVec;
	sf::VertexArray m_verts;
	std::vector<int> m_durations;
	int m_spreadRadius;

	void resetParticle(int p_particleIndex);

public:
	ParticleSys(sf::Color p_color, sf::Vector2f p_position, sf::Vector2f p_movementVec, int p_duration, int p_spreadRadius, int p_numParticles);
	sf::VertexArray& getVerts();
	void processParticles();
	void moveEmitter(const sf::Vector2f &p_vec);
	void setColor(sf::Color p_color);
};
#endif