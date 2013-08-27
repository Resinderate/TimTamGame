#include "Game.h"

Game::Game(sf::RenderWindow &p_window, int p_ballRadius, int p_objectiveTimer, int p_objectiveArc, int p_maxBalls, 
		   int p_minBalls, const sf::Font &p_font, sf::Vector2f p_pointsPosition, int p_pointsSize, 
		   sf::Color p_pointsColor,  int p_pauseDimAlpha, std::string p_backgroundMusicFile, int p_backgroundMusicVolume, 
		   int p_pointsPerBall) :
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
	m_points("", p_font),
	m_clock(),
	m_pauseDim(),
	m_backgroundMusic(),
	m_pointsPerBall(p_pointsPerBall)
{
	srand(time(0));
	for(int i = 0; i < m_averageBalls; i++)
	{
		sf::Vector2f randomStart = SeedStartingRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_obstacles.Append(Ball(randomStart.x, randomStart.y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
	}
	
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
	//This will have to change to something letting it come back to the main menu
	while(m_window->isOpen())
	{
	//Run the game loop.
	HandleEvents();

	if(!m_paused)
	{
		SpawnNewBalls();
		MoveObstacles();
		MoveObstacleReactions();
		CheckCollisions();
		CheckBallsLeavingScreen();
		ProcessObjective();
		AddCumilativePoints();
		GeneratePointsText();
	}

	CheckPause();
	Render();
	}
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
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
	{
		if(CheckCircleCollision(m_player.getCircle(), i.Item().getCircle()))
		{
			int currentHue = i.Item().getHue() % 300;
			if( (currentHue - m_objectiveHue) <= 60 && (currentHue - m_objectiveHue)  >= -60)
				m_player.setMultiplier(m_player.getMultiplier() + 1);
			else
				m_player.setMultiplier(1);	//Back to deafault.

			//Could use the ball color too, check it out
			m_obstacleReactions.Append(AnimatedBall(i.Item().getCircle().getPosition(), sf::Color(i.Item().getColor())));
			m_obstacles.Remove(i);
			//amount of points for a ball
			m_player.addPoints(m_pointsPerBall);
		}
	}
}

void Game::CheckBallsLeavingScreen()
{
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
	{
		if(i.Item().getX() < 0 - m_ballRadius || i.Item().getY() > m_window->getSize().y + m_ballRadius)
		{
			m_obstacles.Remove(i);
		}
	}
}

void Game::ProcessObjective()
{
	if(m_clock.getElapsedTime().asSeconds() > m_objectiveTimer)
	{
		int currentObjectiveHue = m_objectiveHue;
		while(m_objectiveHue == currentObjectiveHue)
		{
			int randIndex = rand() % 3;
			m_objectiveHue = m_objectiveColors[randIndex];
		}
		m_objectiveTriangle.getVerts()[1].color = ColorUtil::HueToRGB(m_objectiveHue);
		m_objectiveTriangle.reset();
		m_clock.restart();
	}

	if(m_objectiveTriangle.isMoving())
		m_objectiveTriangle.move();
}

void Game::AddCumilativePoints()
{
	//add a points per tick to have the points always increasing, adds to the mood of the game
	m_player.addPoints(1);
}

void Game::GeneratePointsText()
{
	std::ostringstream ss;

	ss << "x";
	ss << m_player.getMultiplier();
	ss << " ";
	ss << m_player.getPoints();

	std::string pointsStr = ss.str();
	m_points.setString(sf::String(pointsStr));
}

void Game::CheckPause()
{
	bool pauseKeyDownThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::P);

	if(!m_pausedKeyDown && pauseKeyDownThisFrame)
	{
		if(!m_paused)
		{
			BeginPause();
		}
		else
		{
			EndPause();
		}
	}
	m_pausedKeyDown = pauseKeyDownThisFrame;
}

void Game::Render()
{
	m_window->clear();

	m_window->draw(m_points);
	m_window->draw(m_objectiveTriangle.getVerts());
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
		m_window->draw(i.Item().getCircle());
	for(DListIterator<AnimatedBall> i = m_obstacleReactions.GetIterator(); i.Valid(); i.Forth())
		m_window->draw(i.Item().getCircle());
	m_window->draw(m_player.getCircle());
	if(m_paused)
		m_window->draw(m_pauseDim);
	m_window->display();
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

bool Game::CheckCircleCollision(const sf::CircleShape &p_circle1, const sf::CircleShape &p_circle2)
{
	float xDistance = p_circle1.getPosition().x - p_circle2.getPosition().x;
	float yDistance = p_circle1.getPosition().y - p_circle2.getPosition().y;

	return sqrt((xDistance * xDistance) + (yDistance * yDistance)) < p_circle1.getRadius() + p_circle2.getRadius();
}

void Game::BeginPause()
{
	m_paused = true;
	m_pauseMousePosition.x = sf::Mouse::getPosition().x;
	m_pauseMousePosition.y = sf::Mouse::getPosition().y;
	m_window->setMouseCursorVisible(true);
	m_backgroundMusic.pause();
}

void Game::EndPause()
{
	m_paused = false;
	sf::Mouse::setPosition(m_pauseMousePosition);
	m_window->setMouseCursorVisible(false);
	m_backgroundMusic.play();
}