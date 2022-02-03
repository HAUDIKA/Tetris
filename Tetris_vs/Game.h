#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;

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

	//Helper functions
	bool isOpen();
	void initVariables();


private:

	//Window Variables
	std::unique_ptr<RenderWindow> window;
	VideoMode videomode;
	Event event;



};

