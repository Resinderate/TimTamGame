/*
	Game.h
	Written by Ronan Murphy circa Aug-Sep 2013.
*/
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
	AnimatedVertexArray			m_objectiveTriangle; 
	bool						m_gameOver; 
	bool						m_paused; 
	bool						m_pausedKeyDown; 
	bool						m_retry; 
	bool						m_stillPlaying; 
	Button						m_endQuit; 
	Button						m_endRetry; 
	Button						m_pauseCont; 
	Button						m_pauseQuit; 
	DLinkedList<AnimatedBall>	m_obstacleReactions; 
	DLinkedList<Ball>			m_obstacles; 
	int							m_averageBalls;
	int							m_ballRadius; 
	int							m_endPointsSize; 
	int							m_gameLength; 
	int							m_maxBalls; 
	int							m_minBalls; 
	int							m_objectiveArc; 
	int							m_objectiveHue; 
	int							m_objectiveTimeLength; 
	int							m_pointsPerBall; 
	Player						m_player; 
	sf::Clock					m_gameClock; 
	sf::Clock					m_objectiveClock; 
	sf::Music					m_backgroundMusic; 
	sf::RectangleShape			m_pauseDim; 
	sf::RenderWindow			*m_window; 
	sf::Sound					m_ballBreak; 
	sf::Sound					m_objChange; 
	sf::Text					m_endPoints; 
	sf::Text					m_points; 
	sf::Time					m_gameTimer; 
	sf::Time					m_objectiveTimer; 
	sf::Vector2i				m_pauseMousePosition; 
	std::vector<int>			m_objectiveColors; 

	bool			checkCircleCollision(const sf::CircleShape &p_circle1, const sf::CircleShape &p_circle2);
	sf::Vector2f	seedRandomBallPosition();
	sf::Vector2f	seedStartingRandomBallPosition();
	void			addCumilativePoints();
	void			beginPause();
	void			checkBallsLeavingScreen();
	void			checkCollisions();
	void			checkGameOver();
	void			checkPause();
	void			endPause();
	void			forceQuit();
	void			generatePointsText();
	void			handleEvents();
	void			moveObstacleReactions();
	void			moveObstacles();
	void			processObjective();
	void			processPlayerParticleSys();
	void			render();
	void			spawnNewBalls();
	void			startingHousekeeping();

public:
	Game(sf::RenderWindow &p_window, int p_ballRadius, int p_objectiveTimer, int p_objectiveArc, int p_maxBalls, 
		int m_minBalls, const sf::Font &p_font, sf::Vector2f p_pointsPosition, int p_pointsSize, 
		sf::Color p_pointsColor,  int p_pauseDimAlpha, std::string p_backgroundMusicFile, int p_backgroundMusicVolume, 
		int p_pointsPerBall, int p_gameLength, const Button &p_pauseCont, const Button &p_pauseQuit,
		const Button &p_endRetry, const Button &p_endQuit, int p_endPointsSize, const sf::SoundBuffer &p_ballBreak,
		const sf::SoundBuffer &p_objChange);
	Game();
	bool run();
};
#endif