/*
	Window.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Window
{
private:
	sf::Vector2f m_windowSize;
	sf::ContextSettings m_contextSettings;
	sf::RenderWindow m_window;

public:
	Window();
	Window(sf::Vector2f p_windowSize, const std::string &p_windowName);
	sf::RenderWindow& getWindow();
};
#endif
