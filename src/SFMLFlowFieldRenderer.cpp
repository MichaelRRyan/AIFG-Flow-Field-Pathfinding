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

	m_costText.setCharacterSize(12u);
	
	// If a valid flow field was passed.
	if (m_flowField)
	{
		m_renderTexture.create(
			m_flowField->getWidth() * static_cast<unsigned>(m_cellSize.x),
			m_flowField->getHeight() * static_cast<unsigned>(m_cellSize.y));

		m_renderTextureSprite.setTexture(m_renderTexture.getTexture());
	}
}

void SFMLFlowFieldRenderer::setFlowField(FlowField const * t_flowField)
{
	// If a non-null flow field was passed.
	if (t_flowField)
	{
		m_flowField = t_flowField;

		m_renderTexture.create(
			m_flowField->getWidth() * static_cast<unsigned>(m_cellSize.x),
			m_flowField->getHeight() * static_cast<unsigned>(m_cellSize.y));

		m_renderTextureSprite.setTexture(m_renderTexture.getTexture(), true);
	}
}

void SFMLFlowFieldRenderer::cacheRender(std::list<Vector2u> const * t_path)
{
	if (m_flowField == nullptr) return;

	m_renderTexture.clear();
	auto& cells = m_flowField->getCells();

	sf::VertexArray lines{ sf::Lines };
	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);

	for (unsigned x = 0; x < cells.size(); ++x)
	{
		for (unsigned y = 0; y < cells.at(x).size(); ++y)
		{
			// Continues if this cell is impassable.
			if (!cells.at(x).at(y).isPassable()) continue;

			// Takes some cell info for ease of access.
			unsigned cost = cells.at(x).at(y).cost;
			sf::Vector2f position{ static_cast<float>(x) * m_cellSize.x,
								   static_cast<float>(y) * m_cellSize.y };

			drawHeatmap(rectangle, position, cost);
			drawCostText(position, cost);
			drawVectors(position, cells.at(x).at(y).bestNeighbour, lines);
		}
	}

	if (t_path) drawPath(*t_path);

	m_renderTexture.draw(lines);
	m_renderTexture.display();
}

void ff::SFMLFlowFieldRenderer::drawCostText(sf::Vector2f const& t_position, 
											 unsigned t_cost)
{
	m_costText.setPosition(t_position + m_cellSize / 2.0f);
	m_costText.setString(std::to_string(t_cost));
	sf::FloatRect rect = m_costText.getGlobalBounds();
	m_costText.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	m_renderTexture.draw(m_costText);
}

void ff::SFMLFlowFieldRenderer::drawHeatmap(sf::RectangleShape& t_renderRect, 
											sf::Vector2f const& t_position, 
											unsigned t_cost)
{
	uint8_t value = std::max(50 - static_cast<int>(t_cost), 0) * 5u;
	t_renderRect.setFillColor(sf::Color{ 0u, 0u, value });
	t_renderRect.setPosition(t_position);
	m_renderTexture.draw(t_renderRect);
}

void ff::SFMLFlowFieldRenderer::drawVectors(sf::Vector2f const & t_position,
											Vector2u const & t_bestNeighbour,
											sf::VertexArray & t_lines)
{
	sf::Vector2f neighbourPosition{
		static_cast<float>(t_bestNeighbour.x) * m_cellSize.x,
		static_cast<float>(t_bestNeighbour.y) * m_cellSize.y };

	// Adds the start of the line as the tile position.
	t_lines.append({ t_position + m_cellSize / 2.0f, sf::Color::Blue });

	// Adds the end of the line as the best neighbours position.
	t_lines.append({ neighbourPosition + m_cellSize / 2.0f, sf::Color::White });
}

void ff::SFMLFlowFieldRenderer::drawPath(std::list<Vector2u> const& t_path)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);

	for (auto it = t_path.begin(); it != t_path.end(); ++it)
	{
		sf::Vector2f position{ static_cast<float>(it->x) * m_cellSize.x,
								static_cast<float>(it->y) * m_cellSize.y };

		rectangle.setPosition(position);
		rectangle.setFillColor(sf::Color{ 255u, 0u, 0u });
		m_renderTexture.draw(rectangle);
	}
}

void SFMLFlowFieldRenderer::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_renderTextureSprite, t_states);
}