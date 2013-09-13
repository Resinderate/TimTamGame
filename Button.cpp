/*
	Button.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "Button.h"

/*
	Name:	Constructor
	Desc:	Constructor for Button
	Args:	p_texture,		the texture used for the button
			p_buttonSize,	the size of the button
			p_buttonPos,	the position of the button
			p_nonHoverRect, the part of the texture used when not hovering on the button
			p_hoverRect,	the part of the texture used when hovering on the button
	Rtrn:	None
*/
Button::Button(const sf::Texture &p_texture, const sf::Vector2f &p_buttonSize, const sf::Vector2f &p_buttonPos, sf::IntRect p_nonHoverRect, sf::IntRect p_hoverRect) :
	m_button(p_texture, p_nonHoverRect),
	m_hoverRect(p_hoverRect),
	m_nonHoverRect(p_nonHoverRect)
{
	m_button.setPosition(p_buttonPos);
}

/*
	Name:	getSprite
	Desc:	getter for the sprite of the button
	Args:	None
	Rtrn:	m_button
*/
sf::Sprite& Button::getSprite()
{
	return m_button;
}

/*
	Name:	startHover
	Desc:	sets the button to use the part of the texture needed for when the button is being hovered on
	Args:	None
	Rtrn:	None
*/
void Button::startHover()
{
	m_button.setTextureRect(m_hoverRect);
}

/*
	Name:	endHover
	Desc:	resets the button to used the part of the texture needed when nothing is hovering on the button
	Args:	None
	Rtrn:	None
*/
void Button::endHover()
{
	m_button.setTextureRect(m_nonHoverRect);
}
