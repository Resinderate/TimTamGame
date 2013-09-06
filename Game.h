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
#include "Button.h"

class Game 
{
private:
	sf::RenderWindow *m_window;
	int m_ballRadius;
	int m_objectiveHue;
	int m_objectiveTimeLength;
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
	sf::Clock m_objectiveClock;
	sf::Time m_objectiveTimer;
	sf::RectangleShape m_pauseDim;
	sf::Music m_backgroundMusic;
	int m_pointsPerBall;
	sf::Clock m_gameClock;
	sf::Time m_gameTimer;
	bool m_gameOver;
	int m_gameLength;
	Button m_pauseCont;
	Button m_pauseQuit;
	Button m_endRetry;
	Button m_endQuit;
	bool m_retry;
	bool m_stillPlaying;

	void StartingHousekeeping();
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
	void CheckGameOver();
	void Render();

	sf::Vector2f SeedStartingRandomBallPosition();
	sf::Vector2f SeedRandomBallPosition();
	bool CheckCircleCollision(const sf::CircleShape &p_circle1, const sf::CircleShape &p_circle2);
	void BeginPause();
	void EndPause();
	void ForceQuit();

public:
	Game(sf::RenderWindow &p_window, int p_ballRadius, int p_objectiveTimer, int p_objectiveArc, int p_maxBalls, 
		int m_minBalls, const sf::Font &p_font, sf::Vector2f p_pointsPosition, int p_pointsSize, 
		sf::Color p_pointsColor,  int p_pauseDimAlpha, std::string p_backgroundMusicFile, int p_backgroundMusicVolume, 
		int p_pointsPerBall, int p_gameLength, const Button &p_pauseCont, const Button &p_pauseQuit, const Button &p_endRetry,
		const Button &p_endQuit);
	Game();

	bool Run();
	

};
#endif