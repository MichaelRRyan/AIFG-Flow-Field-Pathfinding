#include "AnimatedSprite.h"

///////////////////////////////////////////////////////////////////////////////
AnimatedSprite::AnimatedSprite() :
	m_currentAnimation{ nullptr },
	m_currentFrame{ -1 }
{
}

///////////////////////////////////////////////////////////////////////////////
void AnimatedSprite::update()
{
	if (m_currentAnimation)
	{
		// Switch to the next frame when enough time has elapsed.
		float secondsSinceLastFrame = m_timeSinceLastFrame.getElapsedTime().asSeconds();
		if (secondsSinceLastFrame > m_currentAnimation->secondsPerFrame)
		{
			// Increment the frame and wrap back to zero if on the last frame.
			m_currentFrame = (m_currentFrame + 1) % 
				m_currentAnimation->frames.size();

			m_sprite.setTextureRect(m_currentAnimation->frames.at(m_currentFrame));
			m_timeSinceLastFrame.restart();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
void AnimatedSprite::loadTexture(std::string const& t_path)
{
	if (!m_texture.loadFromFile(t_path))
		std::cout << "Error loading texture from path " + t_path + "\n";
	else
		m_sprite.setTexture(m_texture);
}

///////////////////////////////////////////////////////////////////////////////
void AnimatedSprite::setAnimation(int t_index)
{
	if (t_index >= 0 && t_index < m_animations.size())
	{
		m_currentAnimation = &m_animations.at(t_index);

		// If there's frames in the new current animation, use the first frame.
		if (!m_currentAnimation->frames.empty())
		{
			m_sprite.setTextureRect(m_currentAnimation->frames.at(0));
			m_currentFrame = 0;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
int AnimatedSprite::createAnimation(std::vector<sf::IntRect> const& t_frames,
									float t_secondsPerFrame)
{
	m_animations.emplace_back(t_frames, t_secondsPerFrame);

	// Returns the index of the new animation.
	return m_animations.size() - 1;
}

///////////////////////////////////////////////////////////////////////////////
void AnimatedSprite::setPosition(sf::Vector2f const& t_position)
{
	m_sprite.setPosition(t_position + m_offset);
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2f const& AnimatedSprite::getPosition() const
{
	return m_sprite.getPosition() - m_offset;
}

///////////////////////////////////////////////////////////////////////////////
void AnimatedSprite::setOffset(sf::Vector2f const& t_offset)
{
	m_offset = t_offset;
}

///////////////////////////////////////////////////////////////////////////////
sf::Vector2f const& AnimatedSprite::getOffset() const
{
	return m_offset;
}

///////////////////////////////////////////////////////////////////////////////
void AnimatedSprite::draw(sf::RenderTarget& t_target, sf::RenderStates t_states) const
{
	t_target.draw(m_sprite, t_states);
}

///////////////////////////////////////////////////////////////////////////////