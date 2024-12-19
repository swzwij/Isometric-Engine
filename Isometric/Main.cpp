#include "Game.cpp"

const Vector2 SCREEN_SIZE(1200, 800);

int main()
{
	try
	{
		Game game(SCREEN_SIZE);
		game.Run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}