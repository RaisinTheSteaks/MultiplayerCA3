#include <RoboCatClientPCH.h>

SFHealthSpriteComponent::SFHealthSpriteComponent(GameObject * inGameObject) :
	SFSpriteComponent(inGameObject)
{
}

sf::Sprite & SFHealthSpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	pos.mX -= 35;
	pos.mY -= 15;

	m_sprite.setPosition(pos.mX, pos.mY);
	int health = mGameObject->GetAsCat()->GetHealth();
	m_sprite.setTexture(*SFTextureManager::sInstance->GetTexture(GetCorrectTexture(health)));

	return m_sprite;
}

std::string SFHealthSpriteComponent::GetCorrectTexture(int health)
{
	if (health > 20)
		return "armor10";
	else if (health > 10)
		return "armor" + std::to_string(health - 10);
	else
		return "health" + std::to_string(health);
}
