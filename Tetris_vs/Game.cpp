#include "Game.h"

//Constructor
Game::Game()
{
	this->initVariables();
	this->start = std::clock();
	this->init_music();
}

//Destructor
Game::~Game()
{

}

//-------Updating--------------------------------------------------------------------------------------------------------------------


//Update the Simulation each simulationstep
void Game::update()
{
	if (!this->gameOver && is_start)
	{
		//Move down piece after time intervall
		this->measured_time = (double)(std::clock() - this->start) / (double)CLOCKS_PER_SEC;
		if (this->measured_time - this->time_intervall > 0)
		{
			current_tile->move_down();
			if (this->collision(current_tile.get()))
			{
				current_tile->move_up();
				this->place_tile();
			}
			this->measured_time = 0;
			this->start = std::clock();
		}
	}

	

	//read user input
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed():
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->gameOver == false && event.key.code == sf::Keyboard::Space)
			{
				if (this->score > this->high_score) this->write_high_score_file();
				this->is_start = true;	
			}
			if(this->is_start == true && event.key.code == sf::Keyboard::E)
			{
				//endGame
				this->restart_game();
			}
			break;
		default: break;
		}

		if (!this->gameOver && is_start)
		{
			switch (this->event.type)
			{
			case(sf::Event::KeyPressed):
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Y)
				{
					this->current_tile->rotate(0);

					if (this->collision(current_tile.get())) this->current_tile->rotate(1);

					this->set_ghost_tile();
				}
				else if (event.key.code == sf::Keyboard::X)
				{
					this->current_tile->rotate(1);
					if (this->collision(current_tile.get())) this->current_tile->rotate(0);
					this->set_ghost_tile();
				}



				else if (event.key.code == sf::Keyboard::Left)
				{
					current_tile->move_left();
					if (this->collision(current_tile.get())) current_tile->move_right();
					this->set_ghost_tile();
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					current_tile->move_right();
					if (this->collision(current_tile.get())) current_tile->move_left();
					this->set_ghost_tile();
				}


				else if (event.key.code == sf::Keyboard::Down && this->isReleased)
				{
					this->isReleased = false;
					this->current_tile->setPosition(this->ghost_tile->getPosition());
					this->place_tile();
				}
				break;

			default:
				this->isReleased = true;
				break;
			}
		}
	}

	this->update_music();

}






//----Rendering---------------------------------------------------------------------------------------------------------------------------

//renders the game for each simulationstep
void Game::render()
{
	this->window->clear(sf::Color(100, 100, 200, 255));
	if (!this->is_start)
	{
		this->window->draw(this->start_screen);
	}
	else
	{
		

		this->drawMatrix();

		this->draw_ghost_tile();
		this->drawTile(this->current_tile.get());
		this->drawTile(this->next_tile.get());

		this->drawScore();
		this->drawLevel();
	}
	this->window->display();
}


void Game::drawTile(Tile* tile)
{
	std::vector<std::vector<int>> temp_tile = tile->getTileshape();
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (temp_tile[row][col] != 0)
			{
				switch (temp_tile[row][col])
				{
				case (1):
					cell.setFillColor(sf::Color::Blue);
					break;
				case 2:
					cell.setFillColor(sf::Color::Yellow);
					break;
				case 3:
					cell.setFillColor(sf::Color::Magenta);
					break;
				case 4:
					cell.setFillColor(sf::Color::Red);
					break;
				case 5:
					cell.setFillColor(sf::Color::Green);
					break;
				case 6:
					cell.setFillColor(sf::Color::Blue);
					break;
				case 7:
					cell.setFillColor(sf::Color::Green);
					break;
				}

				cell.setPosition(sf::Vector2f(col * CELL_SIZE, row * CELL_SIZE) + tile->getPosition());
				this->window->draw(cell);
			}
		}
	}

	sf::RectangleShape square(sf::Vector2f(5 * CELL_SIZE, 5 * CELL_SIZE));
	square.setOutlineColor(sf::Color::White);
	square.setOutlineThickness(5.f);
	square.setFillColor(sf::Color::Transparent);
	square.setPosition(this->next_tile->getPosition() + sf::Vector2f(-CELL_SIZE / 2.f, -CELL_SIZE / 2.f));
	this->window->draw(square);
}

void Game::draw_ghost_tile()
{
	std::vector<std::vector<int>> temp_tile = this->ghost_tile->getTileshape();
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	cell.setOutlineColor(sf::Color::Transparent);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (temp_tile[row][col] != 0)
			{
				cell.setPosition(sf::Vector2f(col * CELL_SIZE, row * CELL_SIZE) + this->ghost_tile->getPosition());
				this->window->draw(cell);
			}
		}
	}
}




void Game::drawMatrix()
{
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
	cell.setFillColor(sf::Color::Red);

	for (int row = 0; row < FIELD_HEIGHT; row++)
	{
		for (int col = 0; col < FIELD_WIDTH; col++)
		{
			switch (this->matrix[row][col])
			{
			case (1):
				cell.setFillColor(sf::Color::Blue);
				break;
			case 2:
				cell.setFillColor(sf::Color::Yellow);
				break;
			case 3:
				cell.setFillColor(sf::Color::Magenta);
				break;
			case 4:
				cell.setFillColor(sf::Color::Red);
				break;
			case 5:
				cell.setFillColor(sf::Color::Green);
				break;
			case 6:
				cell.setFillColor(sf::Color::Blue);
				break;
			case 7:
				cell.setFillColor(sf::Color::Green);
				break;
			default:
				cell.setFillColor(sf::Color::Cyan);
				break;
			}

			cell.setPosition(sf::Vector2f(CELL_SIZE * col, CELL_SIZE * row));
			this->window->draw(cell);
		}
	}
}

void Game::drawScore()
{
	std::ostringstream ss;
	ss << "Score: " << this->score << "\n\nHighscore: " << this->high_score;
	this->text_score.setString(ss.str());
	this->window->draw(this->text_score);
	
	this->window->draw(end_game_info);
}

void Game::drawLevel()
{
	std::ostringstream ss;
	ss << "Level: " << this->level << "\n\nLines destroyed: " << this->current_rows + this->complete_rows;
	this->level_info.setString(ss.str());
	this->window->draw(this->level_info);
}

void Game::pop_line()
{
	bool complete = true;
	int row_count = 0;

	int row = 0;
	while (row < FIELD_HEIGHT)
	{
		complete = true;

		for (auto col = this->matrix[row].begin(); col != this->matrix[row].end(); col++)
		{
			if (!*col)
			{
				complete = false;
				break;
			}
		}
		if (complete)
		{
			this->matrix.erase(matrix.begin() + row);
			this->matrix.insert(matrix.begin(), { 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 });
			
			row_count++;
			this->current_rows++;
		}
		++row;
	}

	if (this->current_rows >= 10)
	{
		this->level++;
		this->time_intervall * 0.95;
		this->complete_rows += this->current_rows;
		this->current_rows = 0;
	}

	if (row_count > 0)	this->score += this->update_score(row_count);
}

void Game::set_ghost_tile()
{
	this->ghost_tile = std::make_unique<Tile>(0);
	this->ghost_tile->setTileshape(this->current_tile->getTileshape());
	this->ghost_tile->setPosition(this->current_tile->getPosition());
	this->ghost_tile->set_furthest();


	while (!this->collision(this->ghost_tile.get()))
	{
		this->ghost_tile->move_down();
	}
	this->ghost_tile->move_up();
}


//-------Game Logic---------------------------------------------------------------------------------------------------------------------------

void Game::create_new_tile()
{
	this->current_tile = std::move(this->next_tile);

	auto temp_furthest_up = this->current_tile->getFurthests().furthest_up;

	current_tile->setPosition(sf::Vector2f(FIELD_WIDTH / 2 * CELL_SIZE - CELL_SIZE, 0.f - temp_furthest_up *CELL_SIZE));

	this->set_ghost_tile();
}

void Game::create_next_tile()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6);
	this->next_tile = std::make_unique<Tile>(dist6(rng));

	this->next_tile->setPosition(sf::Vector2f(525.f, 250.f));
}

bool Game::collision(Tile* tile)
{
	std::vector<std::vector<int>> temp_tile = tile->getTileshape();
	sf::Vector2f temp_position = tile->getPosition();

	auto temp_furthest = tile->getFurthests();

	if (temp_position.x + CELL_SIZE * temp_furthest.furthest_right > FIELD_WIDTH * CELL_SIZE || temp_position.y + temp_furthest.furthest_down * CELL_SIZE > FIELD_HEIGHT * CELL_SIZE || temp_position.x + temp_furthest.furthest_left * CELL_SIZE < 0) return true;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (temp_tile[row][col] != 0 && temp_position.y + row *CELL_SIZE < 0) return true;
			if (temp_tile[row][col] != 0 && matrix[row + (int)(temp_position.y / CELL_SIZE)][col + (int)(temp_position.x / CELL_SIZE)] != 0)
			{
				return true;
			}
		}
	}
	return false;
}

void Game::place_tile()
{
	std::vector<std::vector<int>> temp_tile = current_tile->getTileshape();
	sf::Vector2f temp_position = current_tile->getPosition();

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (temp_tile[row][col] && !matrix[row + (int)(temp_position.y / CELL_SIZE)][col + (int)(temp_position.x / CELL_SIZE)])
			{
				matrix[row + (int)(temp_position.y / CELL_SIZE)][col + (int)(temp_position.x / CELL_SIZE)] = temp_tile[row][col];
			}
		}
	}

	this->pop_line();


	this->create_new_tile();
	this->create_next_tile();

	if (this->collision(current_tile.get()))
	{
		if (this->score > this->high_score) this->write_high_score_file();
		this->gameOver = true;
	}
}

int Game::update_score(int row_count)
{
	double level_multiplier = 1;
	int points = 0;

	if (this->level == 1) level_multiplier = 2;
	else if (this->level < 8) level_multiplier = 3/2;
	else if (this->level > 8) level_multiplier = this->level + 1;

	if (row_count < 2) points = 40;
	else if (row_count < 3) points = 100;
	else if (row_count < 4) points = 300;
	else points = 1200;

	return points * level_multiplier;
}

void Game::update_music()
{
	if (this->music.getStatus()==sf::SoundSource::Stopped)
	{
		this->music.openFromFile("Tetris.ogg");
		this->music.play();
	}
}



//----Helper-functions-------------------------------------------------------------------------------------------------------------------------------



//checks if window is still open
bool Game::isOpen()
{
	return this->window->isOpen() ? true : false;
}




void Game::initField()
{
	std::vector<int> temp_row;

	for (int row_count = 0; row_count < FIELD_HEIGHT; row_count++)
	{
		for (int col_count = 0; col_count < FIELD_WIDTH; col_count++)
		{
			temp_row.push_back(0);
		}
		matrix.push_back(temp_row);
		temp_row.erase(temp_row.begin(), temp_row.end());
	}
}


void Game::init_score()
{
	
	this->text_score.setFont(this->myFont);
	this->text_score.setCharacterSize(20);
	this->text_score.setStyle(sf::Text::Bold);
	this->text_score.setFillColor(sf::Color::White);
	this->text_score.setPosition(sf::Vector2f(450.f, 100.f));
}

void Game::init_level()
{
	this->level_info.setFont(this->myFont);
	this->level_info.setCharacterSize(15);
	this->level_info.setStyle(sf::Text::Bold);
	this->level_info.setFillColor(sf::Color::White);
	this->level_info.setPosition(sf::Vector2f(430.f, 550.f));
}

void Game::init_font()
{
	if (!this->myFont.loadFromFile("PressStart2P-vaV7.ttf"))
		std::cout << "Could not load font." << std::endl;
}

void Game::init_texture()
{
	if (!this->texture.loadFromFile("hDC78ML.png")) {
		std::cout << "Could not load texture" << std::endl;
	}
	this->start_screen.setTexture(this->texture);
}

void Game::init_music()
{
	this->music.openFromFile("Tetris.ogg");
	this->music.play();
}


void Game::read_high_score()
{
	this->high_score_file.open("high_score.txt", std::ios::in);
	high_score_file >> this->high_score;
	high_score_file.close();
}

void Game::write_high_score_file()
{
	this->write_high_score.open("high_score.txt", std::ios::out);
	write_high_score << this->score;
	this->write_high_score.close();
}

void Game::restart_game()
{
	this->gameOver = false;
	this->matrix.clear();
	this->initVariables();
}

//Initialization of Member variables
void Game::initVariables()
{
	this->initField();
	this->create_next_tile();
	this->create_new_tile();
	this->create_next_tile();
	this->videomode.height = 800;
	this->videomode.width = 800;
	this->window = std::make_unique<RenderWindow>(videomode, "Tetris", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);

	this->init_font();

	this->init_score();
	this->init_level();
	this->init_texture();
	this->read_high_score();
	this->score = 0;
	this->is_start = false;

	this->end_game_info.setFont(this->myFont);
	this->end_game_info.setFillColor(sf::Color::White);
	this->end_game_info.setPosition(sf::Vector2f(500.f, 700.f));
	this->end_game_info.setString("  Hit E to\nrestart game");
	this->end_game_info.setCharacterSize(20);

	

	this->complete_rows = 0;
	this->current_rows = 0;
}
