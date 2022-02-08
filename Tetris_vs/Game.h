#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <random>
#include <ctime>
#include <sstream>

#include "Tile.h"

using namespace sf;

const int FIELD_HEIGHT = 20;
const int FIELD_WIDTH = 10;

const int TILE_SIZE = 4;

const int CELL_SIZE = 40;




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
	void drawTile(Tile* tile);
	void draw_ghost_tile();
	void drawMatrix();
	void drawScore();

	void pop_line();

	void set_ghost_tile();

	void create_new_tile();
	void create_next_tile();
	bool collision(Tile* tile);
	void place_tile();

	int update_score(int row_count);

	//Helper functions
	bool isOpen();
	void initVariables();
	void initField();
	bool isGameOver();
	void init_score();

	;

private:

	//Window Variables
	std::unique_ptr<RenderWindow> window;
	VideoMode videomode;
	Event event;

	sf::Text text_score;
	sf::Font myFont;
	std::clock_t start;

	//Game logic
	
	std::unique_ptr<Tile> current_tile;
	std::unique_ptr<Tile> ghost_tile;
	std::unique_ptr<Tile> next_tile;

	std::vector<std::vector<int>> matrix;
	double time_intervall = 0.9;
	double measured_time = 0;
	bool gameOver = false;

	int score = 0;
	int level = 1;
};

