#include "Menu.h"

Menu::Menu(sf::RenderWindow &p_window, Button &p_playButton, Button &p_exitButton, int p_minBalls, int p_maxBalls, int p_ballRadius, int p_backgroundDimAlpha, const sf::Texture &p_logoTexture, const sf::Vector2f &p_logoPos) :
	m_window(&p_window),
	m_playButton(p_playButton),
	m_exitButton(p_exitButton),
	m_backgroundObstacles(),
	m_backgroundDim(),
	m_minBalls(p_minBalls),
	m_maxBalls(p_maxBalls),
	m_avgBalls((m_minBalls + m_maxBalls) / 2),
	m_ballRadius(p_ballRadius),
	m_logo(p_logoTexture)
{
	for(int i = 0; i < m_avgBalls; i++)
	{
		sf::Vector2f randomStart = SeedStartingRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 1); //This is where the velocity is calc'd
		m_backgroundObstacles.Append(Ball(randomStart.x, randomStart.y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
	}

	m_backgroundDim.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_backgroundDim.setFillColor(sf::Color(0, 0, 0, p_backgroundDimAlpha));
	m_backgroundDim.setPosition(0, 0);

	m_logo.setPosition(p_logoPos);
}

bool Menu::Run()
{
	int choice = 0;
	while(m_window->isOpen())
	{
		choice = HandleEvents();
		if(choice == 0)
		{
			if(m_window->isOpen())
			{
				SpawnNewBalls();
				MoveBalls();
				CheckBallsLeavingScreen();
				Render();
			}
		}
		else if(choice == 1)
			return true;
		else
			return false;

	}
}

int Menu::HandleEvents()
{
	//Handle Buttons in here?
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

void Menu::Render()
{
	m_window->clear();
	for(DListIterator<Ball> i = m_backgroundObstacles.GetIterator(); i.Valid(); i.Forth())
		m_window->draw(i.Item().getCircle());
	m_window->draw(m_backgroundDim);
	//Buttons std::vector<Button>::iterator i = m_buttons.begin(); i != m_buttons.end(); i++
	m_window->draw(m_playButton.getSprite());
	m_window->draw(m_exitButton.getSprite());
	m_window->draw(m_logo);
	m_window->display();
}

void Menu::SpawnNewBalls()
{
	int random = rand() % m_maxBalls - m_minBalls; // 0-10 for now.
	int comparison = m_backgroundObstacles.GetCount() - m_minBalls; // 0-10 for now

	if(random >= comparison && comparison != 10)
	{
		sf::Vector2f pos = SeedRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_backgroundObstacles.Append(Ball(pos.x, pos.y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
	}
}

void Menu::MoveBalls()
{
	for(DListIterator<Ball> i = m_backgroundObstacles.GetIterator(); i.Valid(); i.Forth())
		i.Item().Move();
}

void Menu::CheckBallsLeavingScreen()
{
	for(DListIterator<Ball> i = m_backgroundObstacles.GetIterator(); i.Valid(); i.Forth())
	{
		if(i.Item().getX() < 0 - m_ballRadius || i.Item().getY() > m_window->getSize().y + m_ballRadius)
		{
			m_backgroundObstacles.Remove(i);
		}
	}
}

sf::Vector2f Menu::SeedStartingRandomBallPosition()
{
	sf::Vector2f seed;
	seed.x = rand() % m_window->getSize().x; // + 1  ??
	seed.y = rand() % m_window->getSize().y;
	return seed;
}

sf::Vector2f Menu::SeedRandomBallPosition()
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
