#ifndef PATH_FOLLOWER_H
#define PATH_FOLLOWER_H

#include <SFML/Graphics.hpp>
#include <list>
#include "Vector2u.h"

class PathFollower : public sf::Drawable
{
public:

	PathFollower(sf::Vector2f const & t_cellSize = { 16.0f, 16.0f });

	void update();

	void setPath(std::list<ff::Vector2u> * t_path);

	void setPosition(sf::Vector2f const & t_position);
	sf::Vector2f const & getPosition() const;

	void setSecondsPerMovement(float t_movementPerSeconds);
	float getSecondsPerMovement() const;

	void setVisible(bool t_flag);
	bool isVisible() const;

private:

	void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;

	std::list<ff::Vector2u> * m_path;

	sf::RectangleShape m_shape;
	sf::Vector2f m_cellSize;
	sf::Clock m_movementTimer;

	float m_secondsPerMovement;
	bool m_visible;

};

#endif // !PATH_FOLLOWER_H