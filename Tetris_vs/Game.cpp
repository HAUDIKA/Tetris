#include "Game.h"

//Constructor
Game::Game()
{
	this->initVariables();
}

//Destructor
Game::~Game()
{
}
//Update the Simulation each simulationstep
void Game::update()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed():
			window->close();
		}
	}
}


//renders the game for each simulationstep
void Game::render()
{
	this->window->clear(Color::Red);
	this->window->display();
}

//checks if window is still open
bool Game::isOpen()
{
	return this->window->isOpen() ?  true : false;
}

//Initialization of Member variables
void Game::initVariables()
{
	this->videomode.height = 900;
	this->videomode.width = 600;
	this->window = std::make_unique<RenderWindow>(videomode, "Tetris", Style::Titlebar | Style::Close);
}
