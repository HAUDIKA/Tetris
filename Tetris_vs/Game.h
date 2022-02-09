#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <iostream>
#include <random>
#include <ctime>
#include <sstream>
#include <fstream>


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
	void drawLevel();

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
	void init_score();
	void init_level();
	void init_font();

	void init_texture();


	void read_high_score();
	void write_high_score_file();

	void restart_game();

private:

	//Window Variables
	std::unique_ptr<RenderWindow> window;
	VideoMode videomode;
	Event event;

	sf::Text text_score;
	sf::Text end_game_info;
	sf::Text level_info;

	sf::Font myFont;

	sf::Texture texture;
	sf::Sprite start_screen;


	std::clock_t start;

	//Game logic

	bool is_start = false;
	
	std::unique_ptr<Tile> current_tile;
	std::unique_ptr<Tile> ghost_tile;
	std::unique_ptr<Tile> next_tile;

	std::vector<std::vector<int>> matrix;
	double time_intervall = 0.9;
	double measured_time = 0;
	bool isReleased = true;
	bool gameOver = false;

	std::ifstream high_score_file;
	std::ofstream write_high_score;

	int score = 0;
	int level = 1;
	int high_score = 0;
	int complete_rows = 0;
	int current_rows = 0;
};

