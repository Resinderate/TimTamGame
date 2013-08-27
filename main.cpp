#include "Window.h"
#include "Game.h"
#include "ResourceHolder.hpp"
#include "ResourceUtil.h"

int main()
{
	ResourceHolder<sf::Font, Fonts::ID> fonts;
	try
	{
		fonts.load(Fonts::WhiteRabbit, "Assets/whiterabbit.ttf");
	}
	catch(std::runtime_error &e)
	{
		return 1;
	}


	Window mainWindow(sf::Vector2f(800, 600), "TimTam");
	Game game(mainWindow.getWindow(), 15, 10, 120, 20, 10, fonts.get(Fonts::WhiteRabbit), sf::Vector2f(30, 20), 32, sf::Color::White, 180,
		"Assets/background.ogg", 40, 1000);

	game.Run();

	return 0;
}