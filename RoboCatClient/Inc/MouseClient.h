class MouseClient : public Mouse
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new MouseClient() ); }

protected:
	MouseClient();

private:
	SFSpriteComponentPtr m_sprite;
};