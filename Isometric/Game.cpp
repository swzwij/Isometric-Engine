#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include "World.cpp"

class Game
{
public: 
	Game(const Vector2 windowSize)
	{
		_window.create(sf::VideoMode(windowSize.x, windowSize.y), "Isometric");
		_window.setFramerateLimit(60);

		_view = sf::View{ sf::FloatRect(0, 0, windowSize.x, windowSize.y) };
	}

	void Run()
	{
		while (_window.isOpen())
		{
			HandleEvents();
			Update();
			Render();
		}
	}

private:
	void HandleEvents()
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				_window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_view.move(-25, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_view.move(25, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				_view.move(0, -25);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				_view.move(0, 25);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				_view.zoom(0.95f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				_view.zoom(1.05f);
		}
	}

	void Update()
	{
		_window.setView(_view);
	}

	void Render()
	{
		_window.clear(sf::Color(24, 36, 48));

		_world.Render(_window);

		_window.display();
	}

	sf::RenderWindow _window;
	sf::View _view;
	World _world = World(Vector2(10, 10));
};