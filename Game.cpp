/*
	Game.cpp
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
#include "Game.h"

/*
	Name:	Constructor
	Desc:	Constructor for Game
	Args:	p_window,				reference to the window to be used for the game
			p_ballRadius,			radius to be used for the balls in the game
			p_objectiveTimeLength,	the median length of the timer used for the objective
			p_objectiveArc,			the arc of the color wheel to be used to be able to gain a multiplier
			p_maxBalls,				the max amount of obstacles to be in the frame at the same time
			p_minBalls,				the min amount of obstacles to be in the frame at the same time
			p_font,					the font obj to be used for the points in the game
			p_pointsPosition,		the position of the points in the game
			p_pointsSize,			the size of the text used for the points
			p_pointsColor,			the color of the text used for the points
			p_pauseDimAlpha,		the alpha value to be used for when the game is paused
			p_backgroundMusicFile,	the string of the file location for the background music
			p_backgroundMusicVolume,the volume to be used for the background music
			p_pointsPerBall,		the points to be given per ball in the game
			p_gameLength,			the length of the game in seconds
			p_pauseCont,			the button to be used on the pause screen for continueing
			p_pauseQuit,			the button to be used on the pause screen for quitting
			p_endRetry,				the button to be used on the end screen for retrying
			p_endQuit,				the button to be used on the end screen for quitting
			p_endPointsSize,		the size of the font to be used on points at the end of the game
			p_ballBreak,			the SoundBuffer obj to be used for when a ball breaks in game
			p_objChange,			the SoundBuffer obj to be used when the objective color changes in game
	Rtrn:	None
*/
Game::Game(sf::RenderWindow &p_window, int p_ballRadius, int p_objectiveTimeLength, int p_objectiveArc, int p_maxBalls, 
		   int p_minBalls, const sf::Font &p_font, sf::Vector2f p_pointsPosition, int p_pointsSize, 
		   sf::Color p_pointsColor,  int p_pauseDimAlpha, std::string p_backgroundMusicFile, int p_backgroundMusicVolume, 
		   int p_pointsPerBall, int p_gameLength, const Button &p_pauseCont, const Button &p_pauseQuit, const Button &p_endRetry,
		   const Button &p_endQuit, int p_endPointsSize, const sf::SoundBuffer &p_ballBreak, const sf::SoundBuffer &p_objChange) :
m_window(&p_window),
	m_ballRadius(p_ballRadius),
	m_objectiveHue(0),
	m_objectiveTimeLength(p_objectiveTimeLength),
	m_objectiveArc(p_objectiveArc),
	m_objectiveColors(3),
	m_objectiveTriangle(sf::Triangles, 3),
	m_paused(false),
	m_pausedKeyDown(false),
	m_pauseMousePosition(),
	m_maxBalls(p_maxBalls),
	m_minBalls(p_minBalls),
	m_averageBalls((p_maxBalls + p_minBalls) / 2),
	m_obstacles(),
	m_obstacleReactions(),
	m_player(sf::Vector2f(p_window.getSize().x/2, p_window.getSize().y/2), sf::Color::White),
	m_points("", p_font),
	m_objectiveClock(),
	m_pauseDim(),
	m_backgroundMusic(),
	m_pointsPerBall(p_pointsPerBall),
	m_gameClock(),
	m_gameTimer(),
	m_gameOver(false),
	m_gameLength(p_gameLength),
	m_pauseCont(p_pauseCont),
	m_pauseQuit(p_pauseQuit),
	m_endRetry(p_endRetry),
	m_endQuit(p_endQuit),
	m_retry(false),
	m_stillPlaying(true),
	m_endPointsSize(p_endPointsSize),
	m_endPoints("", p_font),
	m_ballBreak(p_ballBreak),
	m_objChange(p_objChange)
{
	for(int i = 0; i < m_averageBalls; i++)
	{
		sf::Vector2f randomStart = seedStartingRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_obstacles.Append(Ball(randomStart, sf::Vector2f(vel*-1, vel), ColorUtil::HueToRGB(hue), hue));
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


	m_pauseDim.setSize(sf::Vector2f(m_window->getSize().x, m_window->getSize().y));
	m_pauseDim.setFillColor(sf::Color(0, 0, 0, p_pauseDimAlpha));
	m_pauseDim.setPosition(0, 0);

	if(!m_backgroundMusic.openFromFile(p_backgroundMusicFile)) {}
	//throw some shit
	m_backgroundMusic.setVolume(p_backgroundMusicVolume);

	m_endPoints.setCharacterSize(p_endPointsSize);
	m_endPoints.setColor(p_pointsColor);

	m_ballBreak.setVolume(30);
	m_objChange.setVolume(45);
}

/*
	Name:	run
	Desc:	main function used to run the game, calling everything else needed to function inside
	Args:	None
	Rtrn:	m_retry,	a bool to determine if the player wants to play again 
*/
bool Game::run()
{
	startingHousekeeping();
	while(m_window->isOpen() && m_stillPlaying)
	{
		//Run the game loop.
		handleEvents();

		if(!m_paused && !m_gameOver)
		{
			spawnNewBalls();
			moveObstacles();
			moveObstacleReactions();
			checkCollisions();
			checkBallsLeavingScreen();
			processObjective();
			processPlayerParticleSys();
			addCumilativePoints();
			generatePointsText();
		}

		if(!m_gameOver)
		{
			checkPause();
			checkGameOver();
		}

		render();
	}
	return m_retry;
}

/*
	Name:	handleEvents
	Desc:	handles all the window events and the events related to the paused and end game screens
	Args:	None
	Rtrn:	None
*/
void Game::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			m_window->close();

		//In game mouse events.
		if(!m_paused && !m_gameOver)
		{
			if(event.type == sf::Event::MouseMoved)
			{
				m_player.setPosition(event.mouseMove.x, event.mouseMove.y);
				m_player.getParticleSys().moveEmitter(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
				//Distance formulae
				int points = sqrt((event.mouseMove.x - m_player.getLastPos().x) * (event.mouseMove.x - m_player.getLastPos().x))
					+	sqrt((event.mouseMove.y - m_player.getLastPos().y) * (event.mouseMove.y - m_player.getLastPos().y));
				m_player.addPoints(points);
				m_player.setLastPosition(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));
			}

			if(event.type == sf::Event::LostFocus)
				beginPause();
			//Feature not implemented due to unforseen problems. Related to pausing the game when the mouse leaves the 
			//window area.
			/*
			if(!sf::IntRect(sf::Vector2i(m_window->getPosition()),
				sf::Vector2i(m_window->getSize())).contains(sf::Mouse::getPosition()))
			{
				BeginPause();
			}
			*/
		}

		//In paused mouse events.
		else if(m_paused && !m_gameOver)
		{
			if(event.type == sf::Event::MouseMoved)
			{
				//Buttons
				if(m_pauseCont.getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
					m_pauseCont.startHover();
				else
					m_pauseCont.endHover();

				if(m_pauseQuit.getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
					m_pauseQuit.startHover();
				else
					m_pauseQuit.endHover();
			}

			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					//Continue
					if(m_pauseCont.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						endPause();
					}
					//Quit
					if(m_pauseQuit.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						forceQuit();
					}
				}
			}
		}

		//Game over
		else
		{
			if(event.type == sf::Event::MouseMoved)
			{
				//Buttons
				if(m_endRetry.getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
					m_endRetry.startHover();
				else
					m_endRetry.endHover();

				if(m_endQuit.getSprite().getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y))
					m_endQuit.startHover();
				else
					m_endQuit.endHover();
			}

			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
				{
					//Continue
					if(m_endRetry.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						m_retry = true;
						forceQuit();
					}
					//Quit
					if(m_endQuit.getSprite().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						forceQuit();
					}
				}
			}
		}
	}
}

/*
	Name:	spawnNewBalls
	Desc:	spawns a new ball if the obstacle list determines it needs one.
			It trys to allow a buffer so that new balls don't simply immediatly respawn once they leave the screen.
			Would lead to clumping.
	Args:	None
	Rtrn:	None
*/
void Game::spawnNewBalls()
{
	int random = rand() % m_maxBalls - m_minBalls;
	int comparison = m_obstacles.GetCount() - m_minBalls;

	if(random >= comparison && comparison != 10)
	{
		sf::Vector2f pos = seedRandomBallPosition();
		int hue = rand() % 359;
		int vel = ((rand() % 3) + 2);
		m_obstacles.Append(Ball(pos,sf::Vector2f(vel*-1, vel), ColorUtil::HueToRGB(hue), hue));
	}
}

/*
	Name:	moveObstacles
	Desc:	moves all the balls in the background of the game
	Args:	None
	Rtrn:	None
*/
void Game::moveObstacles()
{
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
		i.Item().move();
}

/*
	Name:	moveObstacleReactions
	Desc:	processes all the animations that are created once a ball is destroyed.
	Args:	None
	Rtrn:	None
*/
void Game::moveObstacleReactions()
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

/*
	Name:	checkCollisions
	Desc:	checks to see if the player has hit any balls on the screen and if so, removes them and creates the
			related reactions, such as adding point, creating a reaction animation and creating a sound effect
	Args:	None
	Rtrn:	None
*/
void Game::checkCollisions()
{
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
	{
		if(checkCircleCollision(m_player.getCircle(), i.Item().getCircle()))
		{
			int currentHue = i.Item().getHue() % 300;
			if( (currentHue - m_objectiveHue) <= 60 && (currentHue - m_objectiveHue)  >= -60)
				m_player.setMultiplier(m_player.getMultiplier() + 1);
			else
				m_player.setMultiplier(1);	//Back to deafault.

			m_obstacleReactions.Append(AnimatedBall(i.Item().getCircle().getPosition(), sf::Color(i.Item().getColor())));
			m_player.getParticleSys().setColor(i.Item().getColor());
			m_obstacles.Remove(i);

			m_player.addPoints(m_pointsPerBall);
			m_ballBreak.play();
		}
	}
}

/*
	Name:	checkBallsLeavingScreen
	Desc:	checks to see if any balls have left the screen, and if so then removes them.
	Args:	None
	Rtrn:	None
*/
void Game::checkBallsLeavingScreen()
{
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
	{
		if(i.Item().getPosition().x < 0 - m_ballRadius || i.Item().getPosition().y > m_window->getSize().y + m_ballRadius)
			m_obstacles.Remove(i);
	}
}

/*
	Name:	processObjective
	Desc:	processes the UI element of the objective. Rotates the goal color as needed, and if so processes the 
			related animation.
	Args:	None
	Rtrn:	None
*/
void Game::processObjective()
{
	m_objectiveTimer += m_objectiveClock.restart();
	m_gameTimer += m_gameClock.restart();
	if(m_objectiveTimer.asSeconds() > m_objectiveTimeLength)
	{
		int currentObjectiveHue = m_objectiveHue;
		while(m_objectiveHue == currentObjectiveHue)
		{
			int randIndex = rand() % 3;
			m_objectiveHue = m_objectiveColors[randIndex];
		}
		m_objectiveTimeLength = (rand() % 6) + 7;
		m_objectiveTriangle.getVerts()[1].color = ColorUtil::HueToRGB(m_objectiveHue);
		m_objectiveTriangle.reset();
		m_objectiveTimer = sf::Time::Zero;
		m_objChange.play();
	}
	if(m_objectiveTriangle.isMoving())
		m_objectiveTriangle.move();
}

/*
	Name:	addCumilativePoints
	Desc:	adds a constant tick of points to the players total to keep a constant tiempo to the game
			which helps the asthetic.
	Args:	None
	Rtrn:	None
*/
void Game::addCumilativePoints()
{
	m_player.addPoints(1);
}

/*
	Name:	generatePointsText
	Desc:	generates the needed text for the points by retrieveing the players current multiplier and points.
	Args:	None
	Rtrn:	None
*/
void Game::generatePointsText()
{
	std::ostringstream ss;

	ss << "x";
	ss << m_player.getMultiplier();
	ss << " ";
	ss << m_player.getPoints();

	std::string pointsStr = ss.str();
	m_points.setString(sf::String(pointsStr));
}

/*
	Name:	checkPause
	Desc:	checks to see if the game must be paused or unpaused
	Args:	None
	Rtrn:	None
*/
void Game::checkPause()
{
	bool pauseKeyDownThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::P);

	if(!m_pausedKeyDown && pauseKeyDownThisFrame)
	{
		if(!m_paused)
		{
			beginPause();
		}
		else
		{
			endPause();
		}
	}
	m_pausedKeyDown = pauseKeyDownThisFrame;
}

/*
	Name:	render
	Desc:	calls to render all the games information to the window.
	Args:	None
	Rtrn:	None
*/
void Game::render()
{
	m_window->clear();
	if(!m_gameOver)
		m_window->draw(m_points);
	m_window->draw(m_player.getParticleSys().getVerts());
	m_window->draw(m_objectiveTriangle.getVerts());
	for(DListIterator<Ball> i = m_obstacles.GetIterator(); i.Valid(); i.Forth())
		m_window->draw(i.Item().getCircle());
	for(DListIterator<AnimatedBall> i = m_obstacleReactions.GetIterator(); i.Valid(); i.Forth())
		m_window->draw(i.Item().getCircle());
	m_window->draw(m_player.getCircle());
	if(m_paused || m_gameOver)
		m_window->draw(m_pauseDim);
	//if paused, draw pause stuff.
	if(m_paused)
	{
		m_window->draw(m_pauseCont.getSprite());
		m_window->draw(m_pauseQuit.getSprite());
	}
	//if game over, draw game over stuff
	if(m_gameOver)
	{
		m_window->draw(m_endPoints);
		m_window->draw(m_endRetry.getSprite());
		m_window->draw(m_endQuit.getSprite());
	}
	m_window->display();
}

/*
	Name:	seedStartingRandomBallPosition
	Desc:	gives a randomn ball position at the start of the game. Can be anywhere on the screen.
	Args:	None
	Rtrn:	sf::Vector2f,	the position of the new ball
*/
sf::Vector2f Game::seedStartingRandomBallPosition()
{
	sf::Vector2f seed;
	seed.x = rand() % m_window->getSize().x; // + 1  ??
	seed.y = rand() % m_window->getSize().y;
	return seed;
}

/*
	Name:	seedRandomBallPosition
	Desc:	seeds a random ball position for during the game. These spawn along the top and right side of the window, 
			as apposed to anywhere/
	Args:	None
	Rtrn:	sf::Vector2f,	the position of the new ball
*/
sf::Vector2f Game::seedRandomBallPosition()
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

/*
	Name:	checkCircleCollision
	Desc:	given to circles, it will check to see if they are colliding.
	Args:	p_circle1,	the first circle
			p_circle2,	the second circle to check against.
	Rtrn:	bool,	if the two are colliding
*/
bool Game::checkCircleCollision(const sf::CircleShape &p_circle1, const sf::CircleShape &p_circle2)
{
	float xDistance = p_circle1.getPosition().x - p_circle2.getPosition().x;
	float yDistance = p_circle1.getPosition().y - p_circle2.getPosition().y;

	return sqrt((xDistance * xDistance) + (yDistance * yDistance)) < p_circle1.getRadius() + p_circle2.getRadius();
}

/*
	Name:	beginPasue
	Desc:	starts the procedure of a pause. Sets the cursor to be visible and stops the music
	Args:	None
	Rtrn:	None
*/
void Game::beginPause()
{
	m_paused = true;
	m_pauseMousePosition.x = sf::Mouse::getPosition().x;
	m_pauseMousePosition.y = sf::Mouse::getPosition().y;

	//Also related to the previous unimplemented code, with the game pausing when the mouse leaves the window
	/*
	//Need to put the mouse position back onto where the window is, so that is doesnt get stuck on pause after resuming
	if(m_pauseMousePosition.x <= m_window->getPosition().x)
	m_pauseMousePosition.x = m_window->getPosition().x;

	if(m_pauseMousePosition.x >= (m_window->getPosition().x + m_window->getSize().x))
	m_pauseMousePosition.x = (m_window->getPosition().x + m_window->getSize().x);

	if(m_pauseMousePosition.y <= m_window->getPosition().y)
	m_pauseMousePosition.y = m_window->getPosition().y;

	if(m_pauseMousePosition.y >= (m_window->getPosition().y + m_window->getSize().y))
	m_pauseMousePosition.y = (m_window->getPosition().y + m_window->getSize().y);

	*/

	m_window->setMouseCursorVisible(true);
	m_backgroundMusic.pause();
}

/*
	Name:	endPause
	Desc:	ends the current pause, makes the cursor invisible again and resumes the music
	Args:	None
	Rtrn:	None
*/
void Game::endPause()
{
	m_paused = false;
	sf::Mouse::setPosition(m_pauseMousePosition);
	m_window->setMouseCursorVisible(false);
	m_backgroundMusic.play();
	m_gameClock.restart();
	m_objectiveClock.restart();
}

/*
	Name:	startHousekeeping
	Desc:	does some startup managing of the game to make the window envirnment correct
	Args:	None
	Rtrn:	None
*/
void Game::startingHousekeeping()
{
	sf::Mouse::setPosition(sf::Vector2i(m_window->getSize().x/2, m_window->getSize().y/2), *m_window);
	m_window->setMouseCursorVisible(false);
	m_backgroundMusic.play();
	m_objectiveClock.restart();
	m_gameClock.restart();
}

/*
	Name:	checkGameOver
	Desc:	checks to see if the game time is over yet
	Args:	None
	Rtrn:	None
*/
void Game::checkGameOver()
{
	if(m_gameTimer.asSeconds() > m_gameLength)
	{
		m_backgroundMusic.pause();
		m_window->setMouseCursorVisible(true);
		m_gameOver = true;

		std::ostringstream ss;
		ss << m_player.getPoints();
		m_endPoints.setString(ss.str());
		m_endPoints.getGlobalBounds();

		m_endPoints.setOrigin(m_endPoints.getGlobalBounds().width/2, m_endPoints.getGlobalBounds().height/2);
		m_endPoints.setPosition(m_window->getSize().x/2, m_window->getSize().y/3);
	}
}

/*
	Name:	forceQuit
	Desc:	tells the game to quit
	Args:	None
	Rtrn:	None
*/
void Game::forceQuit()
{
	m_stillPlaying = false;
}

/*
	Name:	processPlayerParticleSys
	Desc:	processes the players particle system
	Args:	None
	Rtrn:	None
*/
void Game::processPlayerParticleSys()
{
	m_player.getParticleSys().processParticles();
}