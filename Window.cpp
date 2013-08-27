
#include "Window.h"

Window::Window() :
	m_windowSize(800, 600),
	m_contextSettings(1024, 1024, 16),
	m_window(sf::VideoMode(m_windowSize.x, m_windowSize.y), "New Window", sf::Style::Close, m_contextSettings)
{
	m_window.setFramerateLimit(60);
}

Window::Window(sf::Vector2f p_windowSize, const std::string &p_windowName) :
	m_windowSize(p_windowSize),
	m_contextSettings(1024, 1024, 16),
	m_window(sf::VideoMode(m_windowSize.x, m_windowSize.y), p_windowName, sf::Style::Close, m_contextSettings)
{
	m_window.setFramerateLimit(60);
}

sf::RenderWindow& Window::getWindow()
{
	return m_window;
}
