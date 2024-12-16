#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "IsometricTile.cpp"
#include <iostream>

const Vector2 SCREEN_SIZE(800, 600);

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Isometric");
	window.setFramerateLimit(60);

	sf::Texture tileTexture;
	tileTexture.loadFromFile("tile.png");

	std::vector<IsometricTile> tiles;

	sf::View view{ sf::FloatRect(0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y) };

	view.zoom(3.5f);
	view.move(-275, 400);

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			float height = rand() % 3;
			height = rand() % 2 == 0 ? height : -height;
			height /= 10;

			tiles.push_back(IsometricTile(tileTexture, Vector2(x, y), height));
		}
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				view.move(-5, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				view.move(5, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				view.move(0, -5);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				view.move(0, 5);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				view.zoom(0.99f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				view.zoom(1.01f);

		}

		window.setView(view);

		window.clear(sf::Color(24, 36, 48));

		for (auto& tile : tiles)
			tile.Draw(window);

		window.display();
	}

	return 0;
}