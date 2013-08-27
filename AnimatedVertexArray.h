#ifndef ANIMATEDVERTEXARRAY_H
#define ANIMATEDVERTEXARRAY_H

#include <SFML/Graphics/VertexArray.hpp>

class AnimatedVertexArray 
{
public:
	AnimatedVertexArray(sf::PrimitiveType p_type, unsigned int p_VertexCount);
	void reset();
	void move();
	bool isMoving();
	sf::VertexArray& getVerts();

private:
	sf::VertexArray m_verts;
	bool m_moving;
	int m_duration;
	sf::Vector2f m_xMovStart;
	sf::Vector2f m_xMovEnd;
	sf::Vector2f m_yMovStart;
	sf::Vector2f m_yMovEnd;
};
#endif