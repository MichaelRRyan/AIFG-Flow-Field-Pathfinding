/// Game Title
/// @Author
/// @Date

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif

#include "..\include\Game.h"

int main()
{
	std::cout << "----------------------------------------------------------\n\n";
	std::cout << "Sorry about the size, my laptop has a small screen :(\n\n";
	std::cout << "----------------------------------------------------------\n";
	std::cout << "Controls\n";
	std::cout << "----------------------------------------------------------\n";
	std::cout << "Use left mouse button to change the goal location.\n";
	std::cout << "Use right mouse button to place or remove impassable cells.\n";
	std::cout << "Use middle mouse button to place the path follower.\n";
	std::cout << "Press 'F' to toggle the sheep's movement.\n";
	std::cout << "Press 'D' to toggle the debug mode.\n";
	std::cout << "Press '1' to toggle the costs.\n";
	std::cout << "Press '2' to toggle the vectors.\n";

	Game game;
	game.run();

	return 0;
}
