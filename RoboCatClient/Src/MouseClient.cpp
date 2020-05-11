#include <RoboCatClientPCH.h>

MouseClient::MouseClient()
{
	m_sprite.reset(new SFSpriteComponent(this));
	m_sprite->SetTexture(SFTextureManager::sInstance->GetTexture("heart"));
}