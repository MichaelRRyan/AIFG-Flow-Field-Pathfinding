#include "SFMLFieldRenderer.h"

///////////////////////////////////////////////////////////////////////////////
ff::SFMLFieldRenderer::SFMLFieldRenderer(FlowField const* t_flowField, 
										 sf::Vector2f t_cellSize) :
	m_cellSize{ t_cellSize }
{
	if (!m_spriteSheetTexture.loadFromFile("assets/images/sprite_sheet.png"))
		std::cout << "Error loading sprite sheet from \"assets/images/sprite_sheet.png\".\n";
	else
		m_cellSprite.setTexture(m_spriteSheetTexture);

	setFlowField(t_flowField);
}

///////////////////////////////////////////////////////////////////////////////
void ff::SFMLFieldRenderer::setFlowField(FlowField const* t_flowField)
{
	m_flowField = t_flowField;

	// If a non-null flow field was passed.
	if (t_flowField)
	{
		sf::Vector2u size = {
			m_flowField->getWidth() * static_cast<unsigned>(m_cellSize.x),
			m_flowField->getHeight() * static_cast<unsigned>(m_cellSize.y) };

		m_renderTexture.create(size.x, size.y);

		m_renderTextureSprite.setTexture(m_renderTexture.getTexture(), true);
	}
}

///////////////////////////////////////////////////////////////////////////////
void ff::SFMLFieldRenderer::cacheRender()
{
	m_renderTexture.clear();

	Vector2u size{ m_flowField->getWidth(), m_flowField->getHeight() };
	auto& cells = m_flowField->getCells();

	for (unsigned x = 0; x < size.x; ++x)
	{
		for (unsigned y = 0; y < size.y; ++y)
		{
			m_cellSprite.setPosition(static_cast<float>(x) * m_cellSize.x,
									 static_cast<float>(y) * m_cellSize.y);

			m_cellSprite.setTextureRect({ 48, 32 + ((rand() % 3) * 16), 16, 16 });
			m_renderTexture.draw(m_cellSprite);

			if (!cells.at(x).at(y).isPassable())
			{
				m_cellSprite.move(0.0f, -16.0f);
				m_cellSprite.setTextureRect({ 48, 80, 16, 32 });

				m_renderTexture.draw(m_cellSprite);
			}
		}
	}

	m_renderTexture.display();
}

///////////////////////////////////////////////////////////////////////////////
void ff::SFMLFieldRenderer::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_renderTextureSprite, t_states);
}

///////////////////////////////////////////////////////////////////////////////