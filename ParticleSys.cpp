/*
	ParticleSys.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "ParticleSys.h"

/*
	Name:	Constructor
	Desc:	Constructor for ParticleSys
	Args:	p_color,		the innitial color of the particles to be used.
			p_position,		the innitial position of the emitter for the particleSys
			p_movementVec,	the vector to control the movement of the particles
			p_duration,		the duration of the particles to be alive
			p_spreadRadius, the radius of the spread of particles to be used
			p_numParticles, the number of particles to be used.
	Rtrn:	None
*/
ParticleSys::ParticleSys(sf::Color p_color, sf::Vector2f p_position, sf::Vector2f p_movementVec, int p_duration, int p_spreadRadius, int p_numParticles) :
	m_emitterColor(p_color),
	m_emitterPos(p_position),
	m_movementVec(p_movementVec),
	m_duration(p_duration),
	m_spreadRadius(p_spreadRadius),
	m_verts(sf::PrimitiveType::LinesStrip, p_numParticles),
	m_durations(p_numParticles)
{
	for(int i = 0; i < m_durations.size(); i++)
	{
		resetParticle(i);
		//Innitialize the durations to random stuff so it will stagger properly
		m_durations[i] = rand() % m_duration;
	}
}

/*
	Name:	getVerts
	Desc:	getter for the VertexArray of particles
	Args:	None
	Rtrn:	sf::VertexArry, the array of particles to be rendered usually
*/
sf::VertexArray& ParticleSys::getVerts()
{
	return m_verts;
}

/*
	Name:	processParticles
	Desc:	process all the particles in the array, moving them, changing their alpha and resetting if neccesary
	Args:	None
	Rtrn:	None
*/
void ParticleSys::processParticles()
{
	//m_durations size and m_verts size are the same
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

/*
	Name:	moveEmitter
	Desc:	changes the position of the new particles to be spawned to.
	Args:	p_vec,	the vactor of the new position
	Rtrn:	None
*/
void ParticleSys::moveEmitter(const sf::Vector2f &p_vec)
{
	m_emitterPos = p_vec;
}

/*
	Name:	setColor
	Desc:	changes the color that new particles will be reset to.
	Args:	p_color,	the new color.
	Rtrn:	None
*/
void ParticleSys::setColor(sf::Color p_color)
{
	m_emitterColor = p_color;
}

/*
	Name:	resetParticle
	Desc:	resets a single particle based on the current emitter position and color.
	Args:	p_particleIndex,	the index of the particle to be reset
	Rtrn:	None
*/
void ParticleSys::resetParticle(int p_particleIndex)
{
	//This is code based on when the particles were used as points, instead of lines. Would spread the
	//points out randomly behind the player circle.
	//Reset a particle to a default position based on emitter.
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