#include "PathFollower.h"

///////////////////////////////////////////////////////////////////////////////
PathFollower::PathFollower(sf::Vector2f const& t_cellSize) :
	m_cellSize{ t_cellSize },
	m_visible{ true },
	m_followPath{ true },
	m_path{ nullptr },
	m_secondsPerMovement{ 0.5f }
{
	m_animatedSprite.loadTexture("assets/images/tile_sheet.png");
	m_animatedSprite.setOffset({ 2.0f, -16.0f });
	setupAnimations();
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::update()
{
	m_animatedSprite.update();

	if (m_path == nullptr || m_path->empty()) return;

	if (m_followPath)
	{
		float secondsSinceLastMovement = m_movementTimer.getElapsedTime().asSeconds();
		ff::Vector2u nextCell = m_path->front();

		// If the movement time has elapsed.
		if (secondsSinceLastMovement >= m_secondsPerMovement)
		{
			m_movementTimer.restart();
			m_path->pop_front();

			sf::Vector2f position{ static_cast<float>(nextCell.x) * m_cellSize.x,
								   static_cast<float>(nextCell.y) * m_cellSize.y };

			m_animatedSprite.setPosition(position);
			m_previousPosition = position;
		}
		else
		{
			// Interpolate across the cells.
			float interp = secondsSinceLastMovement / m_secondsPerMovement;
			
			sf::Vector2f nextPosition{ static_cast<float>(nextCell.x) * m_cellSize.x,
									   static_cast<float>(nextCell.y) * m_cellSize.y };

			sf::Vector2f vectorTo = nextPosition - m_previousPosition;

			m_animatedSprite.setPosition(m_previousPosition + vectorTo * interp);

			// Works out which animation to use.
			pickAnimation(vectorTo);
		}
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
	m_animatedSprite.setPosition(t_position);
	m_previousPosition = t_position;
	m_movementTimer.restart();
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2f const& PathFollower::getPosition() const
{
	return m_previousPosition;
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

	if (t_flag)
		m_movementTimer.restart();
	else
		m_animatedSprite.setAnimation(static_cast<int>(Animation::Idle));
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
		t_target.draw(m_animatedSprite, t_states);
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::pickAnimation(sf::Vector2f const& t_vectorTo)
{
	if (t_vectorTo.y == 0.0f)
	{
		if (t_vectorTo.x < 0.0f)
			m_animatedSprite.setAnimation(static_cast<int>(Animation::WalkLeft));
		else
			m_animatedSprite.setAnimation(static_cast<int>(Animation::WalkRight));
	}
	else
	{
		if (t_vectorTo.y < 0.0f)
			m_animatedSprite.setAnimation(static_cast<int>(Animation::WalkUp));
		else
			m_animatedSprite.setAnimation(static_cast<int>(Animation::WalkDown));
	}
}

///////////////////////////////////////////////////////////////////////////////
void PathFollower::setupAnimations()
{
	// Creates the idle animation.
	m_animatedSprite.createAnimation(
		{ { 0, 0, 16, 32 }, { 0, 0, 16, 32 }, { 0, 0, 16, 32 },
		  { 16, 0, 16, 32 }, { 32, 0, 16, 32 }, { 48, 0, 16, 32 }, 
		  { 32, 0, 16, 32 }, { 48, 0, 16, 32 } },
		0.3f
	);

	// Creates the walk down animation.
	m_animatedSprite.createAnimation(
		{ { 0, 32, 16, 32 }, { 16, 32, 16, 32 }, { 32, 32, 16, 32 } },
		0.2f
	);

	// Creates the walk right animation.
	m_animatedSprite.createAnimation(
		{ { 0, 64, 16, 32 }, { 16, 64, 16, 32 }, { 32, 64, 16, 32 } },
		0.2f
	);

	// Creates the walk left animation.
	m_animatedSprite.createAnimation(
		{ { 0, 96, 16, 32 }, { 16, 96, 16, 32 }, { 32, 96, 16, 32 } },
		0.2f
	);

	// Creates the walk up animation.
	m_animatedSprite.createAnimation(
		{ { 0, 128, 16, 32 }, { 16, 128, 16, 32 }, { 32, 128, 16, 32 } },
		0.2f
	);

	m_animatedSprite.setAnimation(static_cast<int>(Animation::Idle));
}

///////////////////////////////////////////////////////////////////////////////