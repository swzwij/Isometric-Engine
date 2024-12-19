#include "Vector2.h"

class InputHandler
{
public:
	static Vector2 ArrowInput(sf::Event& event)
	{
		Vector2 input;

		if (event.key.code == sf::Keyboard::Left)
			input.x - 1;
		if (event.key.code == sf::Keyboard::Right)
			input.x + 1;
		if (event.key.code == sf::Keyboard::Up)
			input.y - 1;
		if (event.key.code == sf::Keyboard::Down)
			input.y + 1;

		return input;
	}

	static Vector2 WASDInput(sf::Event& event)
	{
		Vector2 input;

		if (event.key.code == sf::Keyboard::A)
			input.x - 1;
		if (event.key.code == sf::Keyboard::D)
			input.x + 1;
		if (event.key.code == sf::Keyboard::W)
			input.y - 1;
		if (event.key.code == sf::Keyboard::S)
			input.y + 1;

		return input;
	}

	static Vector2 MouseInput(sf::Event& event, sf::RenderWindow& window, sf::View& view)
	{
		Vector2 input;

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			sf::Vector2f worldPos = window.mapPixelToCoords(mousePos, view);

			input = Vector2(worldPos.x, worldPos.y);
		}

		return input;
	}
};