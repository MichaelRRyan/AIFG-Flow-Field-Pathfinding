#ifndef GAME_H
#define GAME_H

/// @Author Michael Rainsford Ryan

#include <SFML/Graphics.hpp>

/// <summary>
/// The game's main class. Keeps the game running at 60
/// frames per second and holds all ground level game objects.
/// </summary>
class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void setupShapes();

	sf::RenderWindow m_window;
	bool m_exitGame;

	sf::CircleShape m_circle;

};

#endif // !GAME_H

