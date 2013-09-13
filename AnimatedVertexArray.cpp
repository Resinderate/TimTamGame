/*
	AnimatedVertexArray.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "AnimatedVertexArray.h"

/*
	Name:	Constructor
	Desc:	Constructor for AnimatedVertexArray
	Args:	p_type,			the primitive type to be used with the vertex's
			p_vertexcount,	the amount of vertex's to be used.
	Rtrn:	None
*/
AnimatedVertexArray::AnimatedVertexArray(sf::PrimitiveType p_type, unsigned int p_VertexCount) :
	m_verts(p_type, p_VertexCount),
	m_moving(false),
	m_duration(1),
	m_xMovEnd(600, 600),
	m_xMovStart(400, 600),
	m_yMovEnd(800, 400),
	m_yMovStart(800, 200)
{
	m_verts[0].position = sf::Vector2f(800, 400); //Top right - Y
	m_verts[1].position = sf::Vector2f(800, 600); //Centre
	m_verts[2].position = sf::Vector2f(600, 600); //Bot left - X
}


/*
	Name:	reset
	Desc:	resets to the start of the animation
	Args:	None
	Rtrn:	None
*/
void AnimatedVertexArray::reset()
{
	m_verts[0].position = m_yMovStart;
	m_verts[2].position = m_xMovStart;
	m_moving = true;
}

/*
	Name:	move
	Desc:	runs the animation for a frame
	Args:	None
	Rtrn:	None
*/
void AnimatedVertexArray::move()
{
	float yMovement = (m_yMovEnd.y - m_yMovStart.y) / (60 * m_duration); //Based on 60 fps setup.
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

/*
	Name:	isMoving
	Desc:	getter for m_moving, to show the end of the animation
	Args:	None
	Rtrn:	m_moving
*/
bool AnimatedVertexArray::isMoving()
{
	return m_moving;
}

/*
	Name:	getVerts
	Desc:	getter for m_verts, the vertexArray. Used to render the array
	Args:	None
	Rtrn:	m_verts
*/
sf::VertexArray& AnimatedVertexArray::getVerts()
{
	return m_verts;
}
