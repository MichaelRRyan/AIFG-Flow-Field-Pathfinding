#include "SFMLPathRenderer.h"

///////////////////////////////////////////////////////////////////////////////
ff::SFMLPathRenderer::SFMLPathRenderer(sf::Vector2f const & t_cellSize) :
	m_cellSize{ t_cellSize },
	m_path{ nullptr }
{
}

///////////////////////////////////////////////////////////////////////////////
void ff::SFMLPathRenderer::setPath(std::list<ff::Vector2u> * t_path)
{
	m_path = t_path;
}

///////////////////////////////////////////////////////////////////////////////
void ff::SFMLPathRenderer::draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const
{
	if (m_path == nullptr || m_path->empty()) return;

	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);
	rectangle.setFillColor(sf::Color::Yellow);

	auto end = --m_path->end(); // Skips the last as it's drawn separately.
	for (auto it = m_path->begin(); it != end; ++it)
	{
		rectangle.setPosition({ static_cast<float>(it->x) * m_cellSize.x,
								static_cast<float>(it->y) * m_cellSize.y });
		t_target.draw(rectangle, t_states);
	}
}

///////////////////////////////////////////////////////////////////////////////