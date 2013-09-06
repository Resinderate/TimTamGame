#include "Window.h"
#include "Game.h"
#include "ResourceHolder.hpp"
#include "ResourceUtil.h"
#include "Menu.h"
#include "Button.h"

#include <iostream>

int main()
{
	srand(time(0));
	ResourceHolder<sf::Font, Fonts::ID> fonts;
	ResourceHolder<sf::Texture, Textures::ID> textures;
	try
	{
		fonts.load(Fonts::WhiteRabbit, "Assets/whiterabbit.ttf");
		textures.load(Textures::Buttons, "Assets/buttons.png");
		textures.load(Textures::Timtam, "Assets/timtam.png");
	}
	catch(std::runtime_error &e)
	{
		//write to log file
		return 1;
	}

	Button mainPlayButton(textures.get(Textures::Buttons), sf::Vector2f(250,  75), sf::Vector2f(25, 500), sf::IntRect(0, 0, 250, 75), sf::IntRect(0, 75, 250,  75));
	Button mainQuitButton(textures.get(Textures::Buttons), sf::Vector2f(250,  75), sf::Vector2f(525, 500), sf::IntRect(0, 150, 250, 75), sf::IntRect(0, 225, 250,  75));

	Button pauseContButton(textures.get(Textures::Buttons), sf::Vector2f(250, 75), sf::Vector2f(275, 212.5), sf::IntRect(0, 300, 250, 75), sf::IntRect(0, 375, 250, 75));
	Button pauseQuitButton(textures.get(Textures::Buttons), sf::Vector2f(250,  75), sf::Vector2f(275, 312.5), sf::IntRect(0, 150, 250, 75), sf::IntRect(0, 225, 250,  75));

	Button endRetryButton(textures.get(Textures::Buttons), sf::Vector2f(250, 75), sf::Vector2f(25, 500), sf::IntRect(0, 450, 250, 75), sf::IntRect(0, 525, 250, 75));
	Button endQuitButton(textures.get(Textures::Buttons), sf::Vector2f(250,  75), sf::Vector2f(525, 500), sf::IntRect(0, 150, 250, 75), sf::IntRect(0, 225, 250,  75));

	Window mainWindow(sf::Vector2f(800, 600), "TimTam");
	
	
	Menu startMenu(mainWindow.getWindow(), mainPlayButton, mainQuitButton, 10, 20, 15, 45, textures.get(Textures::Timtam), sf::Vector2f(75, 200));

	bool play = startMenu.Run();
	
	while(play)
	{
		Game game(mainWindow.getWindow(), 15, 10, 120, 20, 10, fonts.get(Fonts::WhiteRabbit), sf::Vector2f(30, 20),
		 32, sf::Color::White, 180, "Assets/background.ogg", 40, 1000, 5, pauseContButton, pauseQuitButton, endRetryButton, endQuitButton);
		play = game.Run();
	}

	return 0;
}