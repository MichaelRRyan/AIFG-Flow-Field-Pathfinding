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
}

void SFMLFlowFieldRenderer::setFlowField(FlowField const * t_flowField)
{
	m_flowField = t_flowField;
}

void ff::SFMLFlowFieldRenderer::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	if (m_flowField == nullptr) return;

	auto & costField = m_flowField->getCostField();
	auto & integrationField = m_flowField->getIntegrationField();
	auto & flowField = m_flowField->getFlowField();

	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);

	sf::Text text = m_costText;

	sf::VertexArray lines{ sf::Lines };

	for (int x = 0; x < costField.size(); ++x)
	{
		for (int y = 0; y < costField.at(x).size(); ++y)
		{
			float posX = static_cast<float>(x) * m_cellSize.x;
			float posY = static_cast<float>(y) * m_cellSize.y;

			rectangle.setPosition(posX,	posY);

			text.setPosition(posX + m_cellSize.x / 2.0f, posY + m_cellSize.y / 2.0f);
			text.setString(std::to_string(integrationField.at(x).at(y)).substr(0, 3));
			sf::FloatRect rect = text.getGlobalBounds();
			text.setOrigin(rect.width / 2.0f, rect.height / 2.0f);

			Node2i direction = flowField.at(x).at(y);

			lines.append({ { posX + m_cellSize.x / 2.0f, posY + m_cellSize.y / 2.0f } , sf::Color::Red });
			lines.append({ { posX + static_cast<float>(direction.x) * m_cellSize.x + m_cellSize.x / 2.0f,
							 posY + static_cast<float>(direction.y) * m_cellSize.y + m_cellSize.x / 2.0f } , sf::Color::Blue });

			t_target.draw(rectangle, t_states);
			t_target.draw(text, t_states);
		}
	}

	t_target.draw(lines, t_states);
}
