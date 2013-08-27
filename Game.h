#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <sstream>
#include <vector>

#include "DLinkedList.h"

#include "Ball.h"
#include "Player.h"
#include "ColorUtil.h"
#include "AnimatedVertexArray.h"
#include "AnimatedBall.h"

class Game 
{
private:
	sf::RenderWindow *m_window;
	int m_ballRadius;
	int m_objectiveHue;
	int m_objectiveTimer;
	int m_objectiveArc;
	std::vector<int> m_objectiveColors;
	AnimatedVertexArray m_objectiveTriangle;
	bool m_paused;
	bool m_pausedKeyDown;
	sf::Vector2i m_pauseMousePosition;
	int m_maxBalls;
	int m_minBalls;
	int m_averageBalls;
	DLinkedList<Ball> m_obstacles;
	DLinkedList<AnimatedBall> m_obstacleReactions;
	Player m_player;
	sf::Text m_points;
	sf::Clock m_clock;
	sf::RectangleShape m_pauseDim;
	sf::Music m_backgroundMusic;
	int m_pointsPerBall;

	void HandleEvents();
	void SpawnNewBalls();
	void MoveObstacles();
	void MoveObstacleReactions();
	void CheckCollisions();
	void CheckBallsLeavingScreen();
	void ProcessObjective();
	void AddCumilativePoints();
	void GeneratePointsText();
	void CheckPause();
	void Render();

	sf::Vector2f SeedStartingRandomBallPosition();
	sf::Vector2f SeedRandomBallPosition();
	bool CheckCircleCollision(const sf::CircleShape &p_circle1, const sf::CircleShape &p_circle2);
	void BeginPause();
	void EndPause();


public:
	Game(sf::RenderWindow &p_window, int p_ballRadius, int p_objectiveTimer, int p_objectiveArc, int p_maxBalls, 
		int m_minBalls, const sf::Font &p_font, sf::Vector2f p_pointsPosition, int p_pointsSize, 
		sf::Color p_pointsColor,  int p_pauseDimAlpha, std::string p_backgroundMusicFile, int p_backgroundMusicVolume, 
		int p_pointsPerBall);
	Game();

	void Run();
	

};
#endif