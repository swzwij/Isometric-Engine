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

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
				sf::Vector2f worldPos = _window.mapPixelToCoords(mousePos, _view);

				Vector2 isometricTilePosition = IsometricTile::WorldToIsometric(Vector2(worldPos.x, worldPos.y));

				if (_selectedTile != nullptr)
					_selectedTile->SetSelected(false);

				_selectedTile = _world.GetTileAt(isometricTilePosition);

				if (_selectedTile != nullptr)
					_selectedTile->SetSelected(true);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_view.move(-250, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_view.move(250, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				_view.move(0, -250);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				_view.move(0, 250);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				_view.zoom(0.9f);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				_view.zoom(1.1f);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				_world.Setup();

		}
	}

	void Update()
	{
		_window.setView(_view);
	}

	void Render()
	{
		_window.clear(sf::Color(24, 36, 48));

		_world.Render(_window, _view);

		_window.display();
	}

	sf::RenderWindow _window;
	sf::View _view;
	World _world = World(Vector2(1000, 1000));

	IsometricTile* _selectedTile = nullptr;
};