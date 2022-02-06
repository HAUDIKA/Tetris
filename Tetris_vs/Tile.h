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

 
    
    std::vector<std::vector<int>> getTileshape();
    sf::Vector2f getPosition();
    

    void setPosition(sf::Vector2f new_position);

    void move_down();
    void move_right();
    void move_left();
    void move_up();

    void set_furthest();

    void rotate(int direction);

private:

    std::vector<std::vector<int>> tileshape;
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

