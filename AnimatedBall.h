#ifndef ANIMATEDBALL_H
#define ANIMATEDBALL_H

#include <SFML/Graphics.hpp>

class AnimatedBall
{
public:
	AnimatedBall();
	AnimatedBall(const sf::Vector2f &p_position, sf::Color p_color);
	void update();	//Increases the scale and modifies the alpha
	bool isOver();
	sf::CircleShape getCircle();

private:
	sf::CircleShape m_circle;
	float m_duration;
	sf::Vector2f m_endScale;
	bool m_over;
	int m_alphaReducePerFrame;
	sf::Vector2f m_scaleIncreasePerFrame;
};
#endif