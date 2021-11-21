#ifndef GAME_H
#define GAME_H

/// @Author Michael Rainsford Ryan

#include <SFML/Graphics.hpp>
#include "FlowField.h"
#include "SFMLFlowFieldRenderer.h"
#include "SFMLPathRenderer.h"
#include "SFMLFieldRenderer.h"
#include "PathFollower.h"

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

	void processMousePressedEvents(sf::Event const & t_event);
	void processKeyPressedEvents(sf::Event const & t_event);

	void setupStartMap();

	sf::Vector2i const m_FLOW_FIELD_SIZE;
	sf::Vector2f const m_CELL_SIZE;

	sf::RenderWindow m_window;
	ff::FlowField m_flowField;
	ff::SFMLFlowFieldRenderer m_flowFieldRenderer;
	ff::SFMLPathRenderer m_pathRenderer;
	ff::SFMLFieldRenderer m_fieldRenderer;

	PathFollower m_pathFollower;

	bool m_debugMode;

};

#endif // !GAME_H

