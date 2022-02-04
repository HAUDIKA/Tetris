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
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,1 ,0 });

		Furthests.furthest_down = 4;
		Furthests.furthest_left = 2;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break;

	case 2:
		tileshape.push_back({ 0, 1 ,0 ,0 });
		tileshape.push_back({ 0, 1 ,0 ,0 });
		tileshape.push_back({ 0, 1 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break;

	case 3:
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 1 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;
		break;

	case 4:
		tileshape.push_back({ 0, 1 ,0 ,0 });
		tileshape.push_back({ 0, 1 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break; 

	case 5:
		tileshape.push_back({ 0, 0 ,1 ,0 });
		tileshape.push_back({ 0, 1 ,1 ,0 });
		tileshape.push_back({ 0, 1 ,0 ,0 });
		tileshape.push_back({ 0, 0 ,0 ,0 });

		Furthests.furthest_down = 3;
		Furthests.furthest_left = 1;
		Furthests.furthest_right = 3;
		Furthests.furthest_up = 0;

		break;

	case 6:
		tileshape.push_back({ 0, 0 ,0 ,0 });
		tileshape.push_back({ 1, 1 ,1 ,0 });
		tileshape.push_back({ 0, 1 ,0 ,0 });
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

void Tile::colliosion(int posX, int posY)
{
	
}

std::vector<std::vector<bool>> Tile::getTileshape()
{
	return tileshape;
}

sf::Vector2f Tile::getPosition()
{
	return current_position;
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


void Tile::rotate()
{ 
	
	
}


bool collision()
{
	return false;
}
