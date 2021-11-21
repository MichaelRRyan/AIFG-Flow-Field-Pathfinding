/// @Author Michael Rainsford Ryan

#include "..\include\Game.h"

///////////////////////////////////////////////////////////////////////////////
Game::Game() :
	m_FLOW_FIELD_SIZE{ 50, 50 },
	m_CELL_SIZE{ 20.0f, 20.0f },
	m_flowField{ m_FLOW_FIELD_SIZE.x, m_FLOW_FIELD_SIZE.y },
	m_flowFieldRenderer{ &m_flowField, m_CELL_SIZE },
	m_pathFollower{ m_CELL_SIZE }
{
	m_flowField.setGoal(10, 10);
	m_flowField.generate();
	
	m_flowFieldRenderer.cacheRender();
	m_pathFollower.setVisible(false);
}

///////////////////////////////////////////////////////////////////////////////
Game::~Game()
{
}

///////////////////////////////////////////////////////////////////////////////
void Game::run()
{
	sf::Vector2u windowSize{
		m_FLOW_FIELD_SIZE.x * static_cast<unsigned>(m_CELL_SIZE.x),
		m_FLOW_FIELD_SIZE.y * static_cast<unsigned>(m_CELL_SIZE.y)
	};

	m_window.create(sf::VideoMode{ windowSize.x, windowSize.y, 32u }, "Basic Game");

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

///////////////////////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
			m_window.close();

		else if (sf::Event::MouseButtonPressed == nextEvent.type)
			processMousePressedEvents(nextEvent);

		else if (sf::Event::KeyPressed == nextEvent.type)
			processKeyPressedEvents(nextEvent);
	}
}

///////////////////////////////////////////////////////////////////////////////
void Game::update(sf::Time t_deltaTime)
{
}

///////////////////////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear();
	m_window.draw(m_flowFieldRenderer);
	m_window.draw(m_pathFollower);
	m_window.display();
}

///////////////////////////////////////////////////////////////////////////////
void Game::processMousePressedEvents(sf::Event const& t_event)
{
	ff::Vector2u mouseCell{
		t_event.mouseButton.x / static_cast<int>(m_CELL_SIZE.x),
		t_event.mouseButton.y / static_cast<int>(m_CELL_SIZE.y) };

	if (sf::Mouse::Button::Middle == t_event.mouseButton.button)
	{
		std::list<ff::Vector2u> const* path = m_flowField.getPathToGoal(mouseCell);

		if (path)
		{
			m_pathFollower.setVisible(true);
			m_pathFollower.setPosition({ 
				static_cast<float>(mouseCell.x) * m_CELL_SIZE.x, 
				static_cast<float>(mouseCell.y) * m_CELL_SIZE.x });

			m_flowFieldRenderer.cacheRender(path);
			delete path;
		}
	}
	else
	{
		if (sf::Mouse::Button::Left == t_event.mouseButton.button)
		{
			m_flowField.setGoal(mouseCell);
		}
		else if (sf::Mouse::Button::Right == t_event.mouseButton.button)
		{
			if (m_flowField.getCell(mouseCell).cost == ff::IMPASSABLE_COST)
				m_flowField.clearCell(mouseCell);
			else
				m_flowField.setWall(mouseCell);
		}

		std::list<ff::Vector2u> const * path = nullptr;
		if (m_pathFollower.isVisible())
		{
			sf::Vector2u pos = static_cast<sf::Vector2u>(m_pathFollower.getPosition());
			ff::Vector2u pathStart{
				pos.x / static_cast<unsigned>(m_CELL_SIZE.x),
				pos.y / static_cast<unsigned>(m_CELL_SIZE.y) };

			path = m_flowField.getPathToGoal(pathStart);
		}

		m_pathFollower.setVisible(path != nullptr);
		m_flowFieldRenderer.cacheRender(path);

		delete path;
	}
}

///////////////////////////////////////////////////////////////////////////////
void Game::processKeyPressedEvents(sf::Event const& t_event)
{
	if (sf::Keyboard::Num1 == t_event.key.code)
	{
		m_flowFieldRenderer.setRenderCosts(!m_flowFieldRenderer.getRenderCosts());
		m_flowFieldRenderer.cacheRender();
	}
	else if (sf::Keyboard::Num2 == t_event.key.code)
	{
		m_flowFieldRenderer.setRenderVectors(!m_flowFieldRenderer.getRenderVectors());
		m_flowFieldRenderer.cacheRender();
	}
}

///////////////////////////////////////////////////////////////////////////////