/*
	Menu.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#ifndef MENU_H
#define MENU_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "DLinkedList.h"
#include "Ball.h"
#include "Button.h"
#include "ColorUtil.h"

class Menu
{
private:
	Button				m_exitButton;
	Button				m_playButton;
	DLinkedList<Ball>	m_backgroundObstacles;
	int					m_avgBalls;
	int					m_ballRadius;
	int					m_maxBalls;
	int					m_minBalls;
	sf::RectangleShape	m_backgroundDim;
	sf::RenderWindow	*m_window;
	sf::Sprite			m_logo;

	int				handleEvents();
	sf::Vector2f	seedRandomBallPosition();
	sf::Vector2f	seedStartingRandomBallPosition();
	void			checkBallsLeavingScreen();
	void			moveBalls();
	void			render();
	void			spawnNewBalls();

public:
	Menu(sf::RenderWindow &p_window, Button &p_playButton, Button &p_exitButton, int p_minBalls, int p_maxBalls, 
		int p_ballRadius, int p_backgroundDimAlpha, const sf::Texture &p_logoTexture, const sf::Vector2f &p_logoPos);
	bool run();
};
#endif