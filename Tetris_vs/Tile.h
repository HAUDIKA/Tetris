#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

class Game;

class Tile 
{
public:
    Tile(int randomNumber);
    ~Tile() = default;

    void colliosion(int posX, int posY);
 
    
    std::vector<std::vector<bool>> getTileshape();
    sf::Vector2f getPosition();
    

    void setPosition(sf::Vector2f new_position);

    void move_down();
    void move_right();
    void move_left();
    void move_up();

    

    void rotate();

private:

    std::vector<std::vector<bool>> tileshape;
    sf::Vector2f current_position;
    struct Furthest_indexes {
        int furthest_right;
        int furthest_left;
        int furthest_down;
        int furthest_up;
    } Furthests;
   
public:

    Furthest_indexes getFurthests()
    {
        return this->Furthests;
    }

};

