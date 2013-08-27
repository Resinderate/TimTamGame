#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>

#include "DLinkedList.h"

#include "Ball.h"
#include "Player.h"
#include "ColorUtil.h"
#include "AnimatedVertexArray.h"
#include "AnimatedBall.h"

void HandleEvents(sf::RenderWindow &p_window, Player &p_player, bool p_paused);
void SeedRandomBallPosition(float &p_x, float &p_y, int p_radius);
void SeedStartingRandomBallPosition(float &p_x, float &p_y);
bool CheckCircleCollision(sf::CircleShape p_circle1, sf::CircleShape p_circle2);
void checkPause(bool &p_paused, bool &p_pauseKeyDown, int &p_pauseMouseX, int &p_pauseMouseY, sf::Window &p_window, sf::Music &p_music);
void beginPause(bool &p_paused, int &p_pauseMouseX, int &p_pauseMouseY, sf::Window &p_window, sf::Music &p_music);
void endPause(bool &p_paused, int &p_pauseMouseX, int &p_pauseMouseY, sf::Window &p_window, sf::Music &p_music);

int main()
{
	int screenWidth = 800;
	int screenHeight = 600;
	float xVelocity = -2;
	float yVelocity = 2;
	int ballRadius = 15;

	//initial color to aim for (Red)
	int objectiveHue = 0;
	//Amount of time between when the obj color changes
	int objectiveTimer = 10;

	//pause variables
	bool paused = false;
	bool pauseKeyDown = false;
	int pauseMouseX = 0;
	int pauseMouseY = 0;

	// create the setting, antialising and shit. Need to properly set these up when quality can be compared.
	sf::ContextSettings s1(1024, 1024, 16);

	//create the window
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Tim Tam", sf::Style::Close, s1);
	window.setFramerateLimit(60);

	srand(time(NULL));

	int maxBalls = 20;
	int minBalls = 10;
	int averageBalls = 15;

	DLinkedList<Ball> obstacles;
	DLinkedList<AnimatedBall> obstacleReactions;

	for(int i = 0; i < averageBalls; i++)
	{
		float x = 0;
		float y = 0;

		SeedStartingRandomBallPosition(x, y);
		int hue = rand() % 359; //UNVERIFIED
		int vel = ((rand() % 3) + 2);
		obstacles.Append(Ball(x, y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
	}

	sf::Color white(255, 255, 255, 255);
	sf::Color transparent(0, 0, 0, 0);

	Player p1(400, 300, white);

	//Text stuff. Points.
	sf::Text points;

	sf::Font fontHarabara; //Not harabara anymore
	if(!fontHarabara.loadFromFile("Assets/whiterabbit.ttf"))
		return 5;

	points.setFont(fontHarabara);
	points.setPosition(30, 20);
	points.setCharacterSize(32);
	points.setColor(white);

	//chop off the extra range first - > 300
	//then check  =/-  Arc / 2  => 60
	int objectiveArc = 120;

	int objectiveColors[3];
	objectiveColors[0] = 0;		//Red
	objectiveColors[1] = 120;	//Green
	objectiveColors[2] = 240;	//Blue

	objectiveHue = objectiveColors[0];

	//Objective Color.
	AnimatedVertexArray objectiveTriangle(sf::Triangles, 3);
	objectiveTriangle.getVerts()[0].position = sf::Vector2f(800, 400);
	objectiveTriangle.getVerts()[1].position = sf::Vector2f(800, 600);
	objectiveTriangle.getVerts()[2].position = sf::Vector2f(600, 600);

	objectiveTriangle.getVerts()[0].color = transparent;
	objectiveTriangle.getVerts()[1].color = ColorUtil::HueToRGB(objectiveHue);
	//Start at red, or [0] at the start, may want to start at a random instead ?
	objectiveTriangle.getVerts()[2].color = transparent;


	sf::Clock clock;

	sf::Mouse::setPosition(sf::Vector2i(400, 300), window);
	window.setMouseCursorVisible(false);

	sf::RectangleShape pauseDim;
	pauseDim.setSize(sf::Vector2f(800, 600)); //size of window pls
	pauseDim.setFillColor(sf::Color(0, 0, 0, 180));
	pauseDim.setPosition(0, 0);

	sf::Music backgroundMusic;
	
	if(!backgroundMusic.openFromFile("Assets/background.ogg"))
		return 2;

	backgroundMusic.setVolume(40); //half volume.
	backgroundMusic.play();

	// run the main loop
	while (window.isOpen())
	{

		// handle events
		HandleEvents(window, p1, paused);

		//Logic
		float x = 0;
		float y = 0;

		if(!paused)
		{
			int random = rand() % maxBalls - minBalls; // 0-10 for now.
			int comparison = obstacles.GetCount() - minBalls; // 0-10 for now

			if(random >= comparison && comparison != 10) // The plus one here is just for balancing of the spread of balls. Keeps the average slightly lower, as it was capping a lot and causing clumping.
			{
				SeedRandomBallPosition(x, y, ballRadius);
				int hue = rand() % 359;
				int vel = ((rand() % 3) + 2);
				obstacles.Append(Ball(x, y, vel*-1, vel, ColorUtil::HueToRGB(hue), hue));
			}

			//Move all the balls
			for(DListIterator<Ball> i = obstacles.GetIterator(); i.Valid(); i.Forth())
				i.Item().Move();

			if(obstacleReactions.GetCount() > 0)
			{
				for(DListIterator<AnimatedBall> i = obstacleReactions.GetIterator(); i.Valid(); i.Forth())
				{
					i.Item().update();
					if(i.Item().isOver())
						obstacleReactions.Remove(i);
				}
			}
			
			/*
			p1.getParticleSys().updateTrailPosition(p1.getX(), p1.getY());
			p1.getParticleSys().pushTrail(sf::CircleShape(p1.getParticleSys().getShape()));
			p1.getParticleSys().popTrail();
			p1.getParticleSys().move();
			*/

			//Check if the player is colliding with anyone.
			for(DListIterator<Ball> i = obstacles.GetIterator(); i.Valid(); i.Forth())
			{
				if(CheckCircleCollision(p1.getCircle(), i.Item().getCircle()))
				{
					int currentHue = i.Item().getHue() % 300;
					if( (currentHue - objectiveHue) <= 60 && (currentHue - objectiveHue)  >= -60)
						p1.setMultiplier(p1.getMultiplier() + 1);
					else
						p1.setMultiplier(1);	//Back to deafault.

					obstacleReactions.Append(AnimatedBall(i.Item().getCircle().getPosition(), sf::Color(i.Item().getColor()))); //Could use the ball color too, check it out
					obstacles.Remove(i);
					//amount of points for a ball
					p1.addPoints(1000);
				}
			}

			//Check if any of the balls have left the screen
			for(DListIterator<Ball> i = obstacles.GetIterator(); i.Valid(); i.Forth())
			{
				if(i.Item().getX() < 0 - ballRadius || i.Item().getY() > screenHeight + ballRadius)
				{
					obstacles.Remove(i);
				}
			}

			if(clock.getElapsedTime().asSeconds() > objectiveTimer)
			{
				int currentObjectiveHue = objectiveHue;
				while(objectiveHue == currentObjectiveHue)
				{
					int randIndex = rand() % 3;
					objectiveHue = objectiveColors[randIndex];
				}
				objectiveTriangle.getVerts()[1].color = ColorUtil::HueToRGB(objectiveHue);
				objectiveTriangle.reset();
				clock.restart();
			}

			if(objectiveTriangle.isMoving())
				objectiveTriangle.move();

			//add a points per tick to have the points always increasing
			p1.addPoints(1);

			std::ostringstream ss;

			ss << "x";
			ss << p1.getMultiplier();
			ss << " ";
			ss << p1.getPoints();
			



			std::string pointsStr = ss.str();
			points.setString(pointsStr);
		}

		checkPause(paused, pauseKeyDown, pauseMouseX, pauseMouseY, window, backgroundMusic);

		// draw it
		//need to make some sort of queue for drawing things.
		window.clear();
		
		window.draw(points);
		window.draw(objectiveTriangle.getVerts());
		for(DListIterator<Ball> i = obstacles.GetIterator(); i.Valid(); i.Forth())
			window.draw(i.Item().getCircle());
		for(DListIterator<AnimatedBall> i = obstacleReactions.GetIterator(); i.Valid(); i.Forth())
			window.draw(i.Item().getCircle());
		/*
		for(DListIterator<sf::CircleShape> i = p1.getParticleSys().getTrail().GetIterator(); i.Valid(); i.Forth())
			window.draw(i.Item());
		*/
		window.draw(p1.getCircle());
		if(paused)
			window.draw(pauseDim);
		//window.draw(scanLinesOverlay);
		window.display();
		//x++;
	}

	//Can return some other shit
	return 0;
}

//Prolly gonna need player obj and stuff
void HandleEvents(sf::RenderWindow &p_window, Player &p_player, bool p_paused)
{
	sf::Event event;
	while (p_window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			p_window.close();

		//In game mouse events.
		if(!p_paused)
		{
			if(event.type == sf::Event::MouseMoved)
			{
				p_player.setPosition(event.mouseMove.x, event.mouseMove.y);
				//Distance formulae
				int points = sqrt( (event.mouseMove.x - p_player.getLastX() ) * (event.mouseMove.x - p_player.getLastX() ) )
					+	 sqrt( (event.mouseMove.y - p_player.getLastY() ) * (event.mouseMove.y - p_player.getLastY() ) );
				p_player.addPoints(points);
				p_player.setLastX(event.mouseMove.x);
				p_player.setLastY(event.mouseMove.y);
			}
		}
		//In paused mouse events.
		else
		{

		}
	}
}

void SeedRandomBallPosition(float &p_x, float &p_y, int p_radius)
{
	int screenWidth = 800;
	int screenHeight = 600;
	bool xaxis;
	int random = rand() % 2;
	if(random == 1)
		xaxis = true;
	else
		xaxis = false;

	if(xaxis)
	{
		p_x = rand() % screenWidth + 1;
		p_y = 0 - p_radius;
	}
	else
	{
		p_x = screenWidth + p_radius;
		p_y = rand() % screenHeight + 1;
	}
}

void SeedStartingRandomBallPosition(float &p_x, float &p_y)
{
	int screenWidth = 800;
	int screenHeight = 600;

	p_x = rand() % screenWidth; // + 1  ??
	p_y = rand() % screenHeight;
}

bool CheckCircleCollision(sf::CircleShape p_circle1, sf::CircleShape p_circle2)
{
	float xDistance = p_circle1.getPosition().x - p_circle2.getPosition().x;
	float yDistance = p_circle1.getPosition().y - p_circle2.getPosition().y;

	return sqrt((xDistance * xDistance) + (yDistance * yDistance)) < p_circle1.getRadius() + p_circle2.getRadius();
}

void checkPause(bool &p_paused, bool &p_pauseKeyDown, int &p_pauseMouseX, int &p_pauseMouseY, sf::Window &p_window, sf::Music &p_music)
{
	bool pauseKeyDownThisFrame = sf::Keyboard::isKeyPressed(sf::Keyboard::P);

	if(!p_pauseKeyDown && pauseKeyDownThisFrame)
	{
		if(!p_paused)
		{
			beginPause(p_paused, p_pauseMouseX, p_pauseMouseY, p_window, p_music);
		}
		else
		{
			endPause(p_paused, p_pauseMouseX, p_pauseMouseY, p_window, p_music);
		}
	}
	p_pauseKeyDown = pauseKeyDownThisFrame;
}

void beginPause(bool &p_paused, int &p_pauseMouseX, int &p_pauseMouseY, sf::Window &p_window, sf::Music &p_music)
{
	p_paused = true;
	p_pauseMouseX = sf::Mouse::getPosition().x;
	p_pauseMouseY = sf::Mouse::getPosition().y;
	p_window.setMouseCursorVisible(true);
	p_music.pause();
}

void endPause(bool &p_paused, int &p_pauseMouseX, int &p_pauseMouseY, sf::Window &p_window, sf::Music &p_music)
{
	p_paused = false;
	sf::Mouse::setPosition(sf::Vector2i(p_pauseMouseX, p_pauseMouseY));
	p_window.setMouseCursorVisible(false);
	p_music.play();
}