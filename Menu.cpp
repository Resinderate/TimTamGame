/*
	Menu.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "Menu.h"

/*
	Name:	Constructor
	Desc:	Constructor for Menu
	Args:	p_window,			the window to be used for the menu
			p_playButton,		the button to be used for playing
			p_exitButton,		the button to be used for quiting
			p_minBalls,			the min amount of balls used for the background graphic
			p_maxBalls,			the max amount of balls used for the background graphic
			p_ballRadius,		the radius of the balls in the background
			p_backgoundDimAlpha,the alpha number to be used on the overlay in the background
			p_logoTexture,		the texture of the logo to be used in the middle of the screen
			p_logoPos,			the position of the logo on the screen
	Rtrn:	None
*/
Menu::Menu(sf::RenderWindow &p_window, Button &p_playButton, Button &p_exitButton, int p_minBalls, int p_maxBalls,
		   int p_ballRadius, int p_backgroundDimAlpha, const sf::Texture &p_logoTexture, const sf::Vector2f &p_logoPos) :
	m_window(&p_window),
	m_playButton(p_playButton),
	m_exitButton(p_exitButton),
	m_backgroundObstacles(),
	m_backgroundDim(),
	m_minBalls(p_minBalls),
	m_maxBalls(p_maxBalls),
	m_avgBalls((p_minBalls + p_maxBalls) / 2),
	m_ballRadius(p_ballRadius),
	m_logo(p_logoTexture)
{
	for(int i = 0; i < m_avgBalls; i++)
	{
		sf::Vector2f randomStart = seedStartingRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 1); //This is where the velocity is calc'd
		m_backgroundObstacles.Append(Ball(randomStart, sf::Vector2f(vel*-1, vel), ColorUtil::HueToRGB(hue), hue));
	}

	m_backgroundDim.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_backgroundDim.setFillColor(sf::Color(0, 0, 0, p_backgroundDimAlpha));
	m_backgroundDim.setPosition(0, 0);

	m_logo.setPosition(p_logoPos);
}


/*
	Name:	run
	Desc:	main function used to run the menu, everything is managed from here until the menu is exited
	Args:	None
	Rtrn:	bool,	true if the game should be now played, or false is the user wishes to exit
*/
bool Menu::run()
{
	int choice = 0;
	while(m_window->isOpen())
	{
		choice = handleEvents();
		if(choice == 0)
		{
			if(m_window->isOpen())
			{
				spawnNewBalls();
				moveBalls();
				checkBallsLeavingScreen();
				render();
			}
		}
		else if(choice == 1)
			return true;
		else
			return false;
	}
}

/*
	Name:	handleEvents
	Desc:	handles all the event for the window and the buttons on the screen.
	Args:	None
	Rtrn:	int,	1 if the user wants to play, 2 if the user wants to quit, and 0 if they havent decided yet (no choice)
*/
int Menu::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			m_window->close();

		if(event.type == sf::Event::MouseMoved)
		{
			//Buttons
			if(m_playButton.getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				m_playButton.startHover();
			else
				m_playButton.endHover();

			if(m_exitButton.getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
				m_exitButton.startHover();
			else
				m_exitButton.endHover();
		}

		if(event.type == sf::Event::MouseButtonPressed)
		{
			if(event.mouseButton.button == sf::Mouse::Left)
			{
				//Play
				if(m_playButton.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					return 1;
				}
				//Quit
				if(m_exitButton.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
				{
					return 2;
				}
			}
		}

		return 0;
	}


}

/*
	Name:	render
	Desc:	renders all of the information of the menu to the window
	Args:	None
	Rtrn:	None
*/
void Menu::render()
{
	m_window->clear();
	for(DListIterator<Ball> i = m_backgroundObstacles.GetIterator(); i.Valid(); i.Forth())
		m_window->draw(i.Item().getCircle());
	m_window->draw(m_backgroundDim);
	m_window->draw(m_playButton.getSprite());
	m_window->draw(m_exitButton.getSprite());
	m_window->draw(m_logo);
	m_window->display();
}

/*
	Name:	spawnNewBalls
	Desc:	spawns new balls to the screen, for the graphic in the background.
	Args:	None
	Rtrn:	None
*/
void Menu::spawnNewBalls()
{
	int random = rand() % m_maxBalls - m_minBalls;
	int comparison = m_backgroundObstacles.GetCount() - m_minBalls;

	if(random >= comparison && comparison != 10)
	{
		sf::Vector2f pos = seedRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_backgroundObstacles.Append(Ball(pos, sf::Vector2f(vel*-1, vel), ColorUtil::HueToRGB(hue), hue));
	}
}

/*
	Name:	moveBalls
	Desc:	moves all the balls in the background, based on their movement vector.
	Args:	None
	Rtrn:	None
*/
void Menu::moveBalls()
{
	for(DListIterator<Ball> i = m_backgroundObstacles.GetIterator(); i.Valid(); i.Forth())
		i.Item().move();
}

/*
	Name:	checkBallsLeavingScreen
	Desc:	checks to see if any balls have left the screen, and if they have it removes them
	Args:	None
	Rtrn:	None
*/
void Menu::checkBallsLeavingScreen()
{
	for(DListIterator<Ball> i = m_backgroundObstacles.GetIterator(); i.Valid(); i.Forth())
	{
		if(i.Item().getPosition().x < 0 - m_ballRadius || i.Item().getPosition().y > m_window->getSize().y + m_ballRadius)
		{
			m_backgroundObstacles.Remove(i);
		}
	}
}

/*
	Name:	seedStartingRandomBallPosition
	Desc:	gives a random position of a ball for the start of the background
	Args:	None
	Rtrn:	Vector2f, the new position
*/
sf::Vector2f Menu::seedStartingRandomBallPosition()
{
	sf::Vector2f seed;
	seed.x = rand() % m_window->getSize().x; // + 1  ??
	seed.y = rand() % m_window->getSize().y;
	return seed;
}

/*
	Name:	seedRandomBallPositon
	Desc:	gives a random position of a ball to be spawned
	Args:	None
	Rtrn:	Vector2f, the new position
*/
sf::Vector2f Menu::seedRandomBallPosition()
{
	sf::Vector2f seed;

	bool xaxis;
	int random = rand() % 2;
	if(random == 1)
		xaxis = true;
	else
		xaxis = false;

	if(xaxis)
	{
		seed.x = rand() % m_window->getSize().x + 1;
		seed.y = 0 - m_ballRadius;
	}
	else
	{
		seed.x = m_window->getSize().x + m_ballRadius;
		seed.y = rand() % m_window->getSize().y + 1;
	}

	return seed;
}
