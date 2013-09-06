#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
private:
	sf::Sprite m_button;
	sf::IntRect m_nonHoverRect; //Texture rect
	sf::IntRect m_hoverRect; // Texture Rect

public:
	Button(const sf::Texture &p_texture, const sf::Vector2f &p_buttonSize, const sf::Vector2f &p_buttonPos, sf::IntRect p_nonHoverRect, sf::IntRect p_hoverRect);
	sf::Sprite& getSprite();
	void startHover();
	void endHover();
};
#endif