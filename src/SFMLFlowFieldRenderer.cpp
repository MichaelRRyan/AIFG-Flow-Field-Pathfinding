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

	m_costText.setFillColor(sf::Color::Black);
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

void ff::SFMLFlowFieldRenderer::cacheRender()
{
	if (m_flowField == nullptr) return;

	m_renderTexture.clear();

	auto& costField = m_flowField->getCostField();
	auto& flowField = m_flowField->getFlowField();

	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);

	sf::Text text = m_costText;

	sf::VertexArray lines{ sf::Lines };

	for (int x = 0; x < costField.size(); ++x)
	{
		for (int y = 0; y < costField.at(x).size(); ++y)
		{
			sf::Vector2f position{ static_cast<float>(x) * m_cellSize.x,
							  static_cast<float>(y) * m_cellSize.y };

			int8_t cost = costField.at(x).at(y);

			text.setPosition(position + m_cellSize / 2.0f);
			text.setString(std::to_string(cost));
			sf::FloatRect rect = text.getGlobalBounds();
			text.setOrigin(rect.width / 2.0f, rect.height / 2.0f);

			Node2i directionNode = flowField.at(x).at(y);
			sf::Vector2f direction{ static_cast<float>(directionNode.x) * m_cellSize.x,
									 static_cast<float>(directionNode.y) * m_cellSize.y };

			// Adds the start of the line as the tile position.
			lines.append({ position + m_cellSize / 2.0f, sf::Color::White });

			// Adds the end of the line as the end of the flow field vector.
			lines.append({ position + direction + m_cellSize / 2.0f, sf::Color::Blue });

			rectangle.setPosition(position);

			uint8_t value = std::max(50 - cost, 0) * 5;
			rectangle.setFillColor(sf::Color{ value, value, value });

			m_renderTexture.draw(rectangle);
			m_renderTexture.draw(text);
		}
	}

	m_renderTexture.draw(lines);
	m_renderTexture.display();
	sf::FloatRect bounds = m_renderTextureSprite.getGlobalBounds();
}

void ff::SFMLFlowFieldRenderer::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_renderTextureSprite, t_states);
}
