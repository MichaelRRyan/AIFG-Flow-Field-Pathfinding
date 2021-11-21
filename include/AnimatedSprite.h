#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

struct Animation
{
	std::vector<sf::IntRect> frames;
	float secondsPerFrame;

	Animation(std::vector<sf::IntRect> const & t_frames,
			  float t_secondsPerFrame) :
		frames{ t_frames }, secondsPerFrame{ t_secondsPerFrame } { }
};

class AnimatedSprite : public sf::Drawable
{
public:

	AnimatedSprite();

	void update();

	void loadTexture(std::string const & t_path);

	void setAnimation(int t_index);
	int createAnimation(std::vector<sf::IntRect> const & t_frames,
						float t_secondsPerFrame);

	void setPosition(sf::Vector2f const & t_position);
	sf::Vector2f const & getPosition() const;

	void setOffset(sf::Vector2f const& t_offset);
	sf::Vector2f const & getOffset() const;

private:

	void draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const override;

	std::vector<Animation> m_animations;

	sf::Clock m_timeSinceLastFrame;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_offset;

	Animation * m_currentAnimation;
	int m_currentFrame;

};

#endif // !ANIMATED_SPRITE_H
