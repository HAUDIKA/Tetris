#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	

	auto game = new Game;

	

	while (game->isOpen())
	{

		game->update();

		game->render();
	}

	delete game;

	return 0;
}