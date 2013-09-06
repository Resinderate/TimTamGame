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
	sf::RenderWindow *m_window;
	DLinkedList<Ball> m_backgroundObstacles;
	Button m_playButton;
	Button m_exitButton;
	sf::RectangleShape m_backgroundDim;
	int m_minBalls;
	int m_maxBalls;
	int m_avgBalls;
	int m_ballRadius;
	sf::Sprite m_logo;

	int HandleEvents();
	void Render();
	void SpawnNewBalls();
	void MoveBalls();
	void CheckBallsLeavingScreen();
	sf::Vector2f SeedStartingRandomBallPosition();
	sf::Vector2f SeedRandomBallPosition();

public:
	Menu(sf::RenderWindow &p_window, Button &p_playButton, Button &p_exitButton, int p_minBalls, int p_maxBalls, 
		int p_ballRadius, int p_backgroundDimAlpha, const sf::Texture &p_logoTexture, const sf::Vector2f &p_logoPos);
	bool Run();
};
#endif