#include "PathFollower.h"

///////////////////////////////////////////////////////////////////////////////
PathFollower::PathFollower(sf::Vector2f const& t_cellSize) :
	m_shape{ { t_cellSize } },
	m_cellSize{ t_cellSize },
	m_visible{ true },
	m_followPath{ true },
	m_path{ nullptr },
	m_secondsPerMovement{ 0.5f }
{
	m_shape.setFillColor(sf::Color::Red);
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::update()
{
	if (m_path == nullptr || m_path->empty()) return;

	if (m_followPath 
		&& m_movementTimer.getElapsedTime().asSeconds() > m_secondsPerMovement)
	{
		m_movementTimer.restart();
		ff::Vector2u nextCell = m_path->front();
		m_path->pop_front();
		m_shape.setPosition(static_cast<float>(nextCell.x) * m_cellSize.x, 
							static_cast<float>(nextCell.y) * m_cellSize.y);
	}
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::setPath(std::list<ff::Vector2u>* t_path)
{
	m_path = t_path;
}

///////////////////////////////////////////////////////////////////////////////
std::list<ff::Vector2u>* PathFollower::getPath() const
{
	return m_path;
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::setPosition(sf::Vector2f const& t_position)
{
	m_shape.setPosition(t_position);
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2f const& PathFollower::getPosition() const
{
	return m_shape.getPosition();
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::setSecondsPerMovement(float t_secondsPerMovement)
{
	m_secondsPerMovement = t_secondsPerMovement;
}

///////////////////////////////////////////////////////////////////////////////
float PathFollower::getSecondsPerMovement() const
{
	return m_secondsPerMovement;
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::setVisible(bool t_flag)
{
	m_visible = t_flag;
}

///////////////////////////////////////////////////////////////////////////////
bool PathFollower::isVisible() const
{
	return m_visible;
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::setFollowPath(bool t_flag)
{
	m_followPath = t_flag;
	m_movementTimer.restart();
}

///////////////////////////////////////////////////////////////////////////////
bool PathFollower::isFollowingPath() const
{
	return m_followPath;
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	if (m_visible)
		t_target.draw(m_shape, t_states);
}

///////////////////////////////////////////////////////////////////////////////