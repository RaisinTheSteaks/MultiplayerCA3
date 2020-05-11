#include <RoboCatClientPCH.h>

SFSpriteComponent::SFSpriteComponent(GameObject* inGameObject) :
	mGameObject(inGameObject)
{
	// Add to the render manager.
	SFRenderManager::sInstance->AddComponent(this);
}

SFSpriteComponent::~SFSpriteComponent()
{
	// If there is a new render manager, need to remove it from here when we die.
	SFRenderManager::sInstance->RemoveComponent(this);
}

void SFSpriteComponent::SetTexture(SFTexturePtr inTexture)
{
	auto tSize = inTexture->getSize();
	m_sprite.setTexture(*inTexture);
	m_sprite.setOrigin(tSize.x / 2, tSize.y / 2);
	m_sprite.setScale(sf::Vector2f(1.f * mGameObject->GetScale(), 1.f * mGameObject->GetScale()));
}

sf::Sprite & SFSpriteComponent::GetSprite()
{
	// Update the sprite based on the game object stuff.
	auto pos = mGameObject->GetLocation();
	auto rot = mGameObject->GetRotation();
	m_sprite.setPosition(pos.mX, pos.mY);
	m_sprite.setRotation(rot);

	return m_sprite;
}
