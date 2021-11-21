#ifndef SFML_FLOW_FIELD_RENDERER_H
#define SFML_FLOW_FIELD_RENDERER_H

#include <SFML/Graphics.hpp>
#include "FlowField.h"

namespace ff
{
	class SFMLFlowFieldRenderer : public sf::Drawable
	{
	public:

		SFMLFlowFieldRenderer(FlowField const * t_flowField = nullptr, 
							  sf::Vector2f t_cellSize = sf::Vector2f{ 32.0f, 32.0f });

		void setFlowField(FlowField const * t_flowField);

		void cacheRender(std::list<Vector2u> const * t_path = nullptr);

		void setRenderCosts(bool t_flag);
		void setRenderVectors(bool t_flag);

		bool getRenderCosts() const;
		bool getRenderVectors() const;


	private:

		void drawCostText(sf::Vector2f const& t_position, unsigned t_cost);

		void drawHeatmap(sf::RectangleShape & t_renderRect, 
						 sf::Vector2f const& t_position, 
						 unsigned t_cost);

		void drawVectors(sf::Vector2f const & t_position, 
						 Vector2u const & t_bestNeighbour, 
						 sf::VertexArray& t_lines);

		void drawPath(std::list<Vector2u> const & t_path);

		void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

		FlowField const * m_flowField;

		sf::Vector2f m_cellSize;

		sf::Font m_costFont;
		sf::Text m_costText;

		sf::RenderTexture m_renderTexture;
		sf::Sprite m_renderTextureSprite;

		bool m_renderCosts;
		bool m_renderVectors;

	};
}

#endif // !SFML_FLOW_FIELD_RENDERER_H