#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <random>
#include <ctime>
#include "Tile.h"

using namespace sf;

const int FIELD_HEIGHT = 20;
const int FIELD_WIDTH = 10;

const int TILE_SIZE = 4;

const int CELL_SIZE = 20;




class Game
{
public:
	//Constructor
	Game();
	//Destructor
	~Game();

	//Simulation
	void update();


	void render();
	void drawTile();
	void drawMatrix();
	void pop_line();

	void create_new_tile();
	bool collision();
	void place_tile();


	//Helper functions
	bool isOpen();
	void initVariables();
	void initField();
	bool isGameOver();

	;

private:

	//Window Variables
	std::unique_ptr<RenderWindow> window;
	VideoMode videomode;
	Event event;

	std::clock_t start;

	//Game logic
	
	std::unique_ptr<Tile> current_tile;
	std::vector<std::vector<int>> matrix;
	double time_intervall = 0.9;
	double measured_time = 0;
	bool gameOver = false;
};

