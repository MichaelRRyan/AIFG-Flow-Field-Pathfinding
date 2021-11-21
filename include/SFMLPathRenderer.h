#ifndef SFML_PATH_RENDERER_H
#define SFML_PATH_RENDERER_H

#include <SFML/Graphics.hpp>
#include <list>
#include "Vector2u.h"

namespace ff
{
	class SFMLPathRenderer : public sf::Drawable
	{
	public:

		SFMLPathRenderer(sf::Vector2f const& t_cellSize);

		void setPath(std::list<ff::Vector2u>* t_path);

	private:

		void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;

		std::list<ff::Vector2u>* m_path;
		sf::Vector2f m_cellSize;

	};
}

#endif // !SFML_PATH_RENDERER_H
