#include "Game.cpp"
#include "windows.h"
#include "Vector2.h"

Vector2 SCREEN_SIZE = Vector2
(
	GetSystemMetrics(SM_CXSCREEN),
	GetSystemMetrics(SM_CYSCREEN)
);

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