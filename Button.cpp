#include "Button.h"

Button::Button(const sf::Texture &p_texture, const sf::Vector2f &p_buttonSize, const sf::Vector2f &p_buttonPos, sf::IntRect p_nonHoverRect, sf::IntRect p_hoverRect) :
	m_button(p_texture, p_nonHoverRect),
	m_hoverRect(p_hoverRect),
	m_nonHoverRect(p_nonHoverRect)
{
	m_button.setPosition(p_buttonPos);
}

sf::Sprite& Button::getSprite()
{
	return m_button;
}

void Button::startHover()
{
	m_button.setTextureRect(m_hoverRect);
}

void Button::endHover()
{
	m_button.setTextureRect(m_nonHoverRect);
}
