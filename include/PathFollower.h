#ifndef PATH_FOLLOWER_H
#define PATH_FOLLOWER_H

#include <SFML/Graphics.hpp>
#include <list>
#include "Vector2u.h"
#include "AnimatedSprite.h"

class PathFollower : public sf::Drawable
{
public:

	PathFollower(sf::Vector2f const & t_cellSize = { 16.0f, 16.0f });

	void update();

	void setPath(std::list<ff::Vector2u>* t_path);
	std::list<ff::Vector2u> * getPath() const;

	void setPosition(sf::Vector2f const & t_position);
	sf::Vector2f const & getPosition() const;

	void setSecondsPerMovement(float t_movementPerSeconds);
	float getSecondsPerMovement() const;

	void setVisible(bool t_flag);
	bool isVisible() const;

	void setFollowPath(bool t_flag);
	bool isFollowingPath() const;

private:

	void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;

	void pickAnimation(sf::Vector2f const & t_vectorTo);
	void setupAnimations();

	enum class Animation
	{
		Idle = 0,
		WalkDown = 1,
		WalkRight = 2,
		WalkLeft = 3,
		WalkUp = 4
	};

	std::list<ff::Vector2u> * m_path;
	sf::Vector2f m_previousPosition;

	AnimatedSprite m_animatedSprite;
	sf::Vector2f m_cellSize;
	sf::Clock m_movementTimer;

	float m_secondsPerMovement;
	bool m_visible;
	bool m_followPath;

};

#endif // !PATH_FOLLOWER_H