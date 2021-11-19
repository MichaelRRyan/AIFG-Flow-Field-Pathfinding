#include "SFMLFlowFieldRenderer.h"

using namespace ff;

SFMLFlowFieldRenderer::SFMLFlowFieldRenderer(FlowField const * t_flowField, sf::Vector2f t_cellSize) :
	m_flowField{ t_flowField },
	m_cellSize{ t_cellSize }
{
	if (!m_costFont.loadFromFile("C:/Windows/Fonts/arial.ttf"))
		throw("Error loading Arial font from \"C:/Windows/Fonts/arial.ttf\".");
	else
		m_costText.setFont(m_costFont);

	//m_costText.setFillColor(sf::Color::Black);
	m_costText.setCharacterSize(16u);
	
	// If a valid flow field was passed.
	if (m_flowField)
	{
		sf::Vector2u cellSizeU{ m_cellSize };

		m_renderTexture.create(m_flowField->getWidth() * cellSizeU.x,
							   m_flowField->getHeight() * cellSizeU.y);

		m_renderTextureSprite.setTexture(m_renderTexture.getTexture());
	}
	
}

void SFMLFlowFieldRenderer::setFlowField(FlowField const * t_flowField)
{
	m_flowField = t_flowField;

	// If a valid flow field was passed.
	if (m_flowField)
	{
		sf::Vector2u cellSizeU{ m_cellSize };

		m_renderTexture.create(m_flowField->getWidth() * cellSizeU.x,
							   m_flowField->getHeight() * cellSizeU.y);

		m_renderTextureSprite.setTexture(m_renderTexture.getTexture(), true);
	}
}

void SFMLFlowFieldRenderer::cacheRender()
{
	if (m_flowField == nullptr) return;

	m_renderTexture.clear();

	auto& cells = m_flowField->getCells();

	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);

	sf::VertexArray lines{ sf::Lines };

	for (unsigned x = 0; x < cells.size(); ++x)
	{
		for (unsigned y = 0; y < cells.at(x).size(); ++y)
		{
			// Continues to the next cell if a wall.
			if (cells.at(x).at(y).cost == WALL_COST) continue;

			// Takes some cell info for ease of access.
			unsigned cost = cells.at(x).at(y).cost;
			sf::Vector2f position{ static_cast<float>(x) * m_cellSize.x,
								   static_cast<float>(y) * m_cellSize.y };

			// Sets up the text for this cell.
			m_costText.setPosition(position + m_cellSize / 2.0f);
			m_costText.setString(std::to_string(cost));
			sf::FloatRect rect = m_costText.getGlobalBounds();
			m_costText.setOrigin(rect.width / 2.0f, rect.height / 2.0f);

			// Sets up the rect for this cell.
			rectangle.setPosition(position);
			uint8_t value = std::max(50 - static_cast<int>(cost), 0) * 5u;
			rectangle.setFillColor(sf::Color{ 0u, 0u, value });

			// Draws the text and rect.
			m_renderTexture.draw(rectangle);
			m_renderTexture.draw(m_costText);
			
			// Adds the flow lines.
			Vector2u bestNeighbour = cells.at(x).at(y).bestNeighbour;
			sf::Vector2f neighbourPosition{
				static_cast<float>(bestNeighbour.x) * m_cellSize.x,
				static_cast<float>(bestNeighbour.y) * m_cellSize.y };

			// Adds the start of the line as the tile position.
			lines.append({ position + m_cellSize / 2.0f, sf::Color::Blue });

			// Adds the end of the line as the best neighbours position.
			lines.append({ neighbourPosition + m_cellSize / 2.0f, sf::Color::White });
		}
	}

	m_renderTexture.draw(lines);
	m_renderTexture.display();
	sf::FloatRect bounds = m_renderTextureSprite.getGlobalBounds();
}

void SFMLFlowFieldRenderer::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_renderTextureSprite, t_states);
}
