#include <iostream>
#include <SFML/Graphics.hpp>

#include "Game.h"

int main()
{
	
	Game game;

	game.create_new_tile();

	while (game.isOpen())
	{
		game.update();

		game.render();
	}

	return 0;
} 