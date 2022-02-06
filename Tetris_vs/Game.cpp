#include "Game.h"

//Constructor
Game::Game()
{
	this->initVariables();
	this->start = std::clock();
}

//Destructor
Game::~Game()
{

}

//-------Updating--------------------------------------------------------------------------------------------------------------------


//Update the Simulation each simulationstep
void Game::update()
{
	//read user input
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed():
			window->close();
			break;
		}

		if (!this->gameOver)
		{
			switch (event.type)
			{
			case Event::KeyPressed:

				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Y)
				{
					this->current_tile->rotate(0);
					if (this->collision()) this->current_tile->rotate(1);
				}

				if (event.key.code == sf::Keyboard::X)
				{
					this->current_tile->rotate(1);
					if (this->collision()) this->current_tile->rotate(0);
				}

				if (event.key.code == sf::Keyboard::Left)
				{
					current_tile->move_left();
					if (this->collision()) current_tile->move_right();
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					current_tile->move_right();
					if (this->collision()) current_tile->move_left();
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					current_tile->move_down();
					if (this->collision())
					{
						current_tile->move_up();
						this->place_tile();
					}
				}
			default: break;
			}




		}
	}

	this->measured_time = (double)(std::clock() - this->start) / (double)CLOCKS_PER_SEC;

	if (!this->gameOver)
	{
		//Move down piece after time intervall

		if (this->measured_time - this->time_intervall > 0)
		{
			current_tile->move_down();
			if (this->collision())
			{
				current_tile->move_up();
				this->place_tile();
			}
			this->measured_time = 0;
			this->start = std::clock();
		}
	}
}






//----Rendering---------------------------------------------------------------------------------------------------------------------------

//renders the game for each simulationstep
void Game::render()
{
	this->window->clear(Color::Black);

	this->drawMatrix();

	this->drawTile();

	this->window->display();
}


void Game::drawTile()
{
	std::vector<std::vector<int>> temp_tile = current_tile->getTileshape();
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

				cell.setPosition(sf::Vector2f(col * CELL_SIZE, row * CELL_SIZE) + current_tile->getPosition());
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

void Game::pop_line()
{
	bool complete;



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
			this->time_intervall *= 0.95;
		}
		++row;
	}
}


//-------Game Logic---------------------------------------------------------------------------------------------------------------------------

void Game::create_new_tile()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6);
	current_tile = std::make_unique<Tile>(dist6(rng));

	current_tile->setPosition(sf::Vector2f(FIELD_WIDTH / 2 * CELL_SIZE - CELL_SIZE, 0.f));

}

bool Game::collision()
{

	std::vector<std::vector<int>> temp_tile = current_tile->getTileshape();
	sf::Vector2f temp_position = current_tile->getPosition();

	auto temp_furthest = current_tile->getFurthests();

	if (temp_position.x + CELL_SIZE * temp_furthest.furthest_right > FIELD_WIDTH * CELL_SIZE || temp_position.y + temp_furthest.furthest_down * CELL_SIZE > FIELD_HEIGHT * CELL_SIZE || temp_position.x + temp_furthest.furthest_left * CELL_SIZE < 0) return true;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
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

	if (this->collision())
	{
		this->gameOver = true;
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

bool Game::isGameOver()
{
	return this->gameOver;
}

//Initialization of Member variables
void Game::initVariables()
{
	this->initField();
	this->videomode.height = 900;
	this->videomode.width = 600;
	this->window = std::make_unique<RenderWindow>(videomode, "Tetris", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}
