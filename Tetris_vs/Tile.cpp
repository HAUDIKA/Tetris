#include "Tile.h"
#include "Game.h"

Tile::Tile(int initRandomNumber)
{
	switch (initRandomNumber)
	{
	case 0:
		tileshape.push_back({ 0, 0 ,0 ,0 });
		tileshape.push_back({ 0, 1 ,1 ,0 });
		tileshape.push_back({ 0, 1 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 1;

		break;

	case 1:
		tileshape.push_back({ 0, 0 ,2 ,0 });
		tileshape.push_back({ 0, 0 ,2 ,0 });
		tileshape.push_back({ 0, 0 ,2 ,0 });
		tileshape.push_back({ 0, 0 ,2 ,0 });

		Furthests.furthest_down = 4;
		Furthests.furthest_left = 2;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break;

	case 2:
		tileshape.push_back({ 0, 3 ,0 ,0 });
		tileshape.push_back({ 0, 3 ,0 ,0 });
		tileshape.push_back({ 0, 3 ,3 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break;

	case 3:
		tileshape.push_back({ 0, 0 ,4 ,0 });
		tileshape.push_back({ 0, 0 ,4 ,0 });
		tileshape.push_back({ 0, 4 ,4 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;
		break;

	case 4:
		tileshape.push_back({ 0, 5 ,0 ,0 });
		tileshape.push_back({ 0, 5 ,5 ,0 });
		tileshape.push_back({ 0, 0 ,5 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break; 

	case 5:
		tileshape.push_back({ 0, 0 ,6 ,0 });
		tileshape.push_back({ 0, 6 ,6 ,0 });
		tileshape.push_back({ 0, 6 ,0 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break;

	case 6:
		tileshape.push_back({ 0, 0 ,0 ,0 });
		tileshape.push_back({ 7, 7 ,7 ,0 });
		tileshape.push_back({ 0, 7 ,0 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 0;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 1;

		break;

	default: break;
	}

	this->current_position = sf::Vector2f(0.f, 0.f);
}


std::vector<std::vector<int>> Tile::getTileshape()
{
	return tileshape;
}

sf::Vector2f Tile::getPosition()
{
	return current_position;
}

void Tile::setTileshape(std::vector<std::vector<int>> new_tileshape)
{
	this->tileshape = new_tileshape;
}

void Tile::setPosition(sf::Vector2f new_position)
{
	current_position = new_position;
}

void Tile::move_down()
{
	current_position += sf::Vector2f(0.f, 1.f *  CELL_SIZE);
}

void Tile::move_right()
{
	current_position += sf::Vector2f(1.f * CELL_SIZE, 0.f);
}

void Tile::move_left()
{
	current_position += sf::Vector2f(-1.f * CELL_SIZE, 0.f);
}

void Tile::move_up()
{
	current_position += sf::Vector2f(0.f, -1.f * CELL_SIZE);
}

void Tile::set_furthest()
{
	bool break_flag = false;

	//get furthest_right
	for (int col = 3; col >= 0; col--)
	{
		if (break_flag) break;

		for (int row = 0; row < 4; row++ != 0)
		{
			if (this->tileshape[row][col])
			{
				this->Furthests.furthest_right = col + 1;
				break_flag = true;
				break;
			}
		}
	}
	break_flag = false;

	//get furthest_left
	for (int col = 0; col < 4; col++)
	{
		if (break_flag) break;

		for (int row = 0; row < 4; row++)
		{
			if (this->tileshape[row][col] != 0)
			{
				this->Furthests.furthest_left = col;
				break_flag = true;
				break;
			}
		}
	}
	break_flag = false;


	//get furthest_down
	for (int row = 3; row >= 0; row--)
	{
		if (break_flag) break;

		for (int col = 3; col >= 0; col--)
		{
			if (this->tileshape[row][col] != 0)
			{
				this->Furthests.furthest_down = row+1;
				break_flag = true;
				break;
			}
		}
	}
	break_flag = false;


	//get furthest_up
	for (int row = 0; row < 4; row++)
	{
		if (break_flag) break;

		for (int col = 3; col >= 0; col--)
		{
			if (this->tileshape[row][col] != 0)
			{
				this->Furthests.furthest_up = row;
				break_flag = true; 
				break;
			}
		}
	}
	break_flag = false;
}


void Tile::rotate(int direction)
{ 

	std::vector<std::vector<int>> temp_tileshape = { { 0, 0 ,0 ,0 }, { 0, 0 ,0 ,0 },{ 0, 0 ,0 ,0 }, { 0, 0 ,0 ,0 } };
	
		switch (direction)	
		{
	
		case 0: //clockwise

			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					int index = 12 + row - (col * 4);
					int new_col = index % 4;
					int new_row = (int)(index / 4);

					temp_tileshape[new_row][new_col] = this->tileshape[row][col];
				}
			}
			break;
			//col2 = (row1 + px - py)

			//row2 = (px + py - col1 - 4)

		case 1: //counter-clockwise

			for (int row = 0; row < 4; row++)
			{
				for (int col = 0; col < 4; col++)
				{
					int index = 3 - row + (col*4);
					int new_col = index % 4;
					int new_row = (int)(index / 4);

					temp_tileshape[new_row][new_col] = this->tileshape[row][col];
				}				 
			}

			break;
	}
	
	this->tileshape = temp_tileshape;
	this->set_furthest();
}



