#ifndef PATH_FOLLOWER_H
#define PATH_FOLLOWER_H

#include <SFML/Graphics.hpp>

class PathFollower : public sf::Drawable
{
public:

	PathFollower(sf::Vector2f const & t_cellSize = { 16.0f, 16.0f });

	void setPosition(sf::Vector2f const & t_position);
	sf::Vector2f const & getPosition() const;

	void setVisible(bool t_flag);
	bool isVisible() const;

private:

	void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;

	sf::RectangleShape m_shape;
	sf::Vector2f m_tileSize;
	bool m_visible;

};

#endif // !PATH_FOLLOWER_H