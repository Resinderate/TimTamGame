#include "ParticleSys.h"

ParticleSys::ParticleSys(sf::Color p_color, sf::Vector2f p_position, sf::Vector2f p_movementVec, int p_duration, int p_spreadRadius, int p_numParticles) :
	m_emitterColor(p_color),
	m_emitterPos(p_position),
	m_movementVec(p_movementVec),
	m_duration(p_duration),
	m_spreadRadius(p_spreadRadius),
	m_verts(sf::PrimitiveType::LinesStrip, p_numParticles),
	m_durations(p_numParticles)
{
	//Innitialize the verts?
	for(int i = 0; i < m_durations.size(); i++)
	{
		resetParticle(i);
		m_durations[i] = rand() % m_duration;
	}
	//Innitialize the durations to random shit
}

sf::VertexArray& ParticleSys::getVerts()
{
	return m_verts;
}

void ParticleSys::processParticles()
{
	
	//durations size and verts size are the same
	for(int i = 0; i < m_durations.size(); i++)
	{
		//Move all the verts.
		m_verts[i].position += m_movementVec;
		//Adjust the timers
		m_durations[i]--;
		//Adjust the transparency
		//For every tick it adjusts downwards to full transparency
		m_verts[i].color.a = m_verts[i].color.a - (255 / m_duration);
		//if any have timed out reset them to default
		if(m_durations[i] <= 0)
			resetParticle(i);
	}
	
}

void ParticleSys::moveEmitter(const sf::Vector2f &p_vec)
{
	m_emitterPos = p_vec;
}

void ParticleSys::setColor(sf::Color p_color)
{
	m_emitterColor = p_color;
}

void ParticleSys::resetParticle(int p_particleIndex)
{
	//reset a particle to a default position based on emitter
	/*
	float randOne = ((float) rand()) / (float) RAND_MAX;
	float randTwo = ((float) rand()) / (float) RAND_MAX;
	//Random angle between 0-2PI
	float randAngle = randOne * (2 * M_PI);
	//random radius between 0-r
	float randRadius = randTwo * m_spreadRadius;

	sf::Vector2f position(randRadius*cos(randAngle), randRadius*sin(randAngle));
	position += m_emitterPos;
	*/

	m_verts[p_particleIndex].color = m_emitterColor;
	m_verts[p_particleIndex].position = m_emitterPos;
	m_durations[p_particleIndex] = m_duration;
}