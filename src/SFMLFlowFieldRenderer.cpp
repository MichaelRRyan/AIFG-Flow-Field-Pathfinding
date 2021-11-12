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
}

void SFMLFlowFieldRenderer::setFlowField(FlowField const * t_flowField)
{
	m_flowField = t_flowField;
}

void ff::SFMLFlowFieldRenderer::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	if (m_flowField == nullptr) return;

	auto & costField = m_flowField->getCostField();

	sf::RectangleShape rectangle;
	rectangle.setSize(m_cellSize);

	sf::Text text = m_costText;

	for (int x = 0; x < costField.size(); ++x)
	{
		for (int y = 0; y < costField.at(x).size(); ++y)
		{
			rectangle.setPosition(static_cast<float>(x) * m_cellSize.x, 
								  static_cast<float>(y) * m_cellSize.y);

			text.setPosition(static_cast<float>(x) * m_cellSize.x,
							 static_cast<float>(y) * m_cellSize.y);

			text.setString(std::to_string(costField.at(x).at(y)));

			t_target.draw(rectangle, t_states);
			t_target.draw(text, t_states);
		}
	}
}
