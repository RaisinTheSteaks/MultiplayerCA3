#pragma once

typedef shared_ptr< sf::Texture >	SFTexturePtr;
typedef shared_ptr<sf::Font> FontPtr;

class SFSpriteComponent
{
public:

	SFSpriteComponent(GameObject* inGameObject);
	~SFSpriteComponent();

	void SetTexture(SFTexturePtr inTexture);
	virtual sf::Sprite& GetSprite();

protected:

	sf::Sprite m_sprite;

	//don't want circular reference...
	GameObject* mGameObject;
};

class SFHealthSpriteComponent : public SFSpriteComponent
{
public:
	SFHealthSpriteComponent(GameObject* inGameObject);
	sf::Sprite& GetSprite();

private:
	std::string GetCorrectTexture(int health);
};

typedef shared_ptr< SFSpriteComponent >	SFSpriteComponentPtr;
typedef shared_ptr< SFHealthSpriteComponent >	SFHealthSpriteComponentPtr;
