#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	

	sf::VideoMode videomode;
	videomode.height = 600;
	videomode.width = 300;

	sf::RenderWindow window(videomode, "Tetris", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed():
				window.close();
			}
		}


		window.clear();
		window.display();

	}

	std::cout << "Hello World!" << std::endl;
	return 0;
} 