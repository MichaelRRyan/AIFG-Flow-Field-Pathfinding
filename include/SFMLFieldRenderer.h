#ifndef SFML_FIELD_RENDERER_H
#define SFML_FIELD_RENDERER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "FlowField.h"

namespace ff
{
	class SFMLFieldRenderer : public sf::Drawable
	{
	public:

		SFMLFieldRenderer(FlowField const* t_flowField = nullptr,
						  sf::Vector2f t_cellSize = sf::Vector2f{ 32.0f, 32.0f });

		void setFlowField(FlowField const* t_flowField);

		void cacheRender();

	private:

		void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;

		FlowField const* m_flowField;
		sf::Vector2f m_cellSize;

		sf::Texture m_spriteSheetTexture;
		sf::Sprite m_cellSprite;

		sf::RenderTexture m_renderTexture;
		sf::Sprite m_renderTextureSprite;

	};
}

#endif // !SFML_FIELD_RENDERER_H
