/*
	Window.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "Window.h"

/*
	Name:	Default Constructor
	Desc:	Default Constructor for Window
	Args:	None
	Rtrn:	None
*/
Window::Window() :
	m_windowSize(800, 600),
	m_contextSettings(24, 8, 16),
	m_window(sf::VideoMode(m_windowSize.x, m_windowSize.y), "New Window", sf::Style::Close, m_contextSettings)
{
	m_window.setFramerateLimit(60);
}

/*
	Name:	Constructor
	Desc:	Constructor for Menu
	Args:	p_windowSize,	the size of the window
			p_windowName,	the name to appear on the window
	Rtrn:	None
*/
Window::Window(sf::Vector2f p_windowSize, const std::string &p_windowName) :
	m_windowSize(p_windowSize),
	m_contextSettings(24, 8, 16),
	m_window(sf::VideoMode(m_windowSize.x, m_windowSize.y), p_windowName, sf::Style::Close, m_contextSettings)
{
	m_window.setFramerateLimit(60);
}

/*
	Name:	getWindow
	Desc:	returns the actual  RenderWindow that this class encapsulates.
	Args:	None
	Rtrn:	sf::RenderWindow, the current window.
*/
sf::RenderWindow& Window::getWindow()
{
	return m_window;
}
