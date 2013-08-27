#include "AnimatedVertexArray.h"

AnimatedVertexArray::AnimatedVertexArray(sf::PrimitiveType p_type, unsigned int p_VertexCount) :
	m_verts(p_type, p_VertexCount),
	m_moving(false),
	m_duration(1),
	m_xMovEnd(600, 600),
	m_xMovStart(400, 600), //TBD, Change me
	m_yMovEnd(800, 400),
	m_yMovStart(800, 200) //TBD, Change me
{
	m_verts[0].position = sf::Vector2f(800, 400); //Top right - Y
	m_verts[1].position = sf::Vector2f(800, 600); //Centre
	m_verts[2].position = sf::Vector2f(600, 600); //Bot left - X
}

void AnimatedVertexArray::reset()
{
	m_verts[0].position = m_yMovStart;
	m_verts[2].position = m_xMovStart;
	m_moving = true;
}

void AnimatedVertexArray::move()
{
	float yMovement = (m_yMovEnd.y - m_yMovStart.y) / (60 * m_duration); //BASED ON 60 FPS
	m_verts[0].position.y += yMovement; //about 1.667 for now

	float xMovement = (m_xMovEnd.x - m_xMovStart.x) / (60 * m_duration);
	m_verts[2].position.x += xMovement;

	if(m_verts[0].position.y > m_yMovEnd.y)
	{
		m_moving = false;
		m_verts[0].position.y = m_yMovEnd.y;
	}
	if(m_verts[2].position.x > m_xMovEnd.x)
	{
		m_moving = false;
		m_verts[2].position.x = m_xMovEnd.x;
	}
}

bool AnimatedVertexArray::isMoving()
{
	return m_moving;
}

sf::VertexArray& AnimatedVertexArray::getVerts()
{
	return m_verts;
}
