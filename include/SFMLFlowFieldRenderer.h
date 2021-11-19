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

		void cacheRender();

	private:

		void draw(sf::RenderTarget & t_target, sf::RenderStates t_states) const override;

		FlowField const * m_flowField;

		sf::Vector2f m_cellSize;

		sf::Font m_costFont;
		sf::Text m_costText;

		sf::RenderTexture m_renderTexture;
		sf::Sprite m_renderTextureSprite;
	};
}

#endif // !SFML_FLOW_FIELD_RENDERER_H