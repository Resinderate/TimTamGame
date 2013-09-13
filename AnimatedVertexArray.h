/*
	AnimatedVertexArray.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef ANIMATEDVERTEXARRAY_H
#define ANIMATEDVERTEXARRAY_H

#include <SFML/Graphics/VertexArray.hpp>

class AnimatedVertexArray 
{
private:
	bool			m_moving;
	int				m_duration;
	sf::Vector2f	m_xMovEnd;
	sf::Vector2f	m_xMovStart;
	sf::Vector2f	m_yMovEnd;
	sf::Vector2f	m_yMovStart;
	sf::VertexArray m_verts;

public:
	AnimatedVertexArray(sf::PrimitiveType p_type, unsigned int p_VertexCount);
	sf::VertexArray&	getVerts();
	bool				isMoving();
	void				move();
	void				reset();
};
#endif