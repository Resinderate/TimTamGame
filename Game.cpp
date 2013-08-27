#include "Game.h"

Game::Game(sf::RenderWindow &p_window, int p_ballRadius, int p_objectiveTimer, int p_objectiveArc, int p_maxBalls, int p_minBalls, std::string p_pointsFontFile, sf::Vector2f p_pointsPosition, int p_pointsSize, sf::Color p_pointsColor,  int p_pauseDimAlpha, std::string p_backgroundMusicFile, int p_backgroundMusicVolume) :
	m_window(&p_window),
	m_ballRadius(p_ballRadius), //15
	m_objectiveHue(0),
	m_objectiveTimer(p_objectiveTimer), //10
	m_objectiveArc(p_objectiveArc), //120
	m_objectiveColors(3),
	m_objectiveTriangle(sf::Triangles, 3),
	m_paused(false),
	m_pausedKeyDown(false),
	m_pauseMousePosition(),
	m_maxBalls(p_maxBalls), //30
	m_minBalls(p_minBalls), //20
	m_averageBalls((p_maxBalls + p_minBalls) / 2),
	m_obstacles(),
	m_obstacleReactions(),
	m_player(p_window.getSize().x/2, p_window.getSize().y/2, sf::Color::White),
	m_points(),
	m_clock(),
	m_pauseDim(),
	m_backgroundMusic()
{
	srand(time(0));
	for(int i = 0; i < m_averageBalls; i++)
	{
		sf::Vector2f randomStart = SeedStartingRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_obstacles.Append(Ball(randomStart.x, randomStart.y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
	}
	sf::Font fontRabbit;
	if(!fontRabbit.loadFromFile(p_pointsFontFile)) {}
	//throw some shit
	m_points.setFont(fontRabbit);
	m_points.setPosition(p_pointsPosition);
	m_points.setCharacterSize(p_pointsSize);
	m_points.setColor(p_pointsColor);

	m_objectiveColors[0] = 0;	//Red
	m_objectiveColors[1] = 120;	//Green
	m_objectiveColors[2] = 240;	//Blue

	m_objectiveTriangle.getVerts()[0].position = sf::Vector2f(800, 400);
	m_objectiveTriangle.getVerts()[1].position = sf::Vector2f(800, 600);
	m_objectiveTriangle.getVerts()[2].position = sf::Vector2f(600, 600);

	m_objectiveTriangle.getVerts()[0].color = sf::Color::Transparent;
	m_objectiveTriangle.getVerts()[1].color = ColorUtil::HueToRGB(m_objectiveHue);
	m_objectiveTriangle.getVerts()[2].color = sf::Color::Transparent;

	sf::Mouse::setPosition(sf::Vector2i(m_window->getSize().x/2, m_window->getSize().y/2), *m_window);
	m_window->setMouseCursorVisible(false);
	m_pauseDim.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_pauseDim.setFillColor(sf::Color(0, 0, 0, p_pauseDimAlpha));
	m_pauseDim.setPosition(0, 0);

	if(!m_backgroundMusic.openFromFile(p_backgroundMusicFile)) {}
	//throw some shit
	m_backgroundMusic.setVolume(p_backgroundMusicVolume);
	m_backgroundMusic.play();
}

void Game::Run()
{
	//Run the game loop.


	//Handle Events

	//if not paused
	//Spawn any new balls
	//Move the balls
	//Move the broken ball animations
	//Check collision
	//Check if any balls have left the screeen
	//Change Objective color if needed, and animate
	//Add extra points
	//Generate Points Text

	//Render
	//If paused render extra stuff
}

void Game::HandleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			m_window->close();

		//In game mouse events.
		if(!m_paused)
		{
			if(event.type == sf::Event::MouseMoved)
			{
				m_player.setPosition(event.mouseMove.x, event.mouseMove.y);
				//Distance formulae
				int points = sqrt( (event.mouseMove.x - m_player.getLastX() ) * (event.mouseMove.x - m_player.getLastX() ) )
					+	 sqrt( (event.mouseMove.y - m_player.getLastY() ) * (event.mouseMove.y - m_player.getLastY() ) );
				m_player.addPoints(points);
				m_player.setLastX(event.mouseMove.x);
				m_player.setLastY(event.mouseMove.y);
			}
		}
		//In paused mouse events.
		else
		{

		}
	}
}

void Game::SpawnNewBalls()
{
	int random = rand() % m_maxBalls - m_minBalls; // 0-10 for now.
	int comparison = m_obstacles.GetCount() - m_minBalls; // 0-10 for now

	if(random >= comparison && comparison != 10)
	{
		sf::Vector2f pos = SeedRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_obstacles.Append(Ball(pos.x, pos.y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
	}
}

void Game::MoveObstacles()
{
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
		i.Item().Move();
}

void Game::MoveObstacleReactions()
{
	if(m_obstacleReactions.GetCount() > 0)
	{
		for(DListIterator<AnimatedBall> i = m_obstacleReactions.GetIterator(); i.Valid(); i.Forth())
		{
			i.Item().update();
			if(i.Item().isOver())
				m_obstacleReactions.Remove(i);
		}
	}
}

void Game::CheckCollisions()
{

}

void Game::CheckBallsLeavingScreen()
{

}

void Game::ProcessObjective()
{

}

void Game::AddCumilativePoints()
{

}

void Game::GeneratePointsText()
{

}

void Game::Render()
{

}


sf::Vector2f Game::SeedStartingRandomBallPosition()
{
	sf::Vector2f seed;
	seed.x = rand() % m_window->getSize().x; // + 1  ??
	seed.y = rand() % m_window->getSize().y;
	return seed;
}

sf::Vector2f Game::SeedRandomBallPosition()
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
		seed.x = rand() % m_window->getSize().y + 1;
		seed.y = 0 - m_ballRadius;
	}
	else
	{
		seed.x = m_window->getSize().x + m_ballRadius;
		seed.y = rand() % m_window->getSize().y + 1;
	}

	return seed;
}