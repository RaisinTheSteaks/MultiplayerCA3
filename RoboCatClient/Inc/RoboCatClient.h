class RoboCatClient : public RoboCat
{
public:
	static	GameObjectPtr	StaticCreate()		{ return GameObjectPtr( new RoboCatClient() ); }

	virtual void Update();
	virtual void	HandleDying() override;

	virtual void	Read( InputMemoryBitStream& inInputStream ) override;

	void DoClientSidePredictionAfterReplicationForLocalCat( uint32_t inReadState );
	void DoClientSidePredictionAfterReplicationForRemoteCat( uint32_t inReadState );



protected:
	RoboCatClient();


private:
	sf::Vector2f		mCatInfo;
	void InterpolateClientSidePrediction( float inOldRotation, const Vector3& inOldLocation, const Vector3& inOldVelocity, bool inIsForRemoteCat );

	float				mTimeLocationBecameOutOfSync;
	float				mTimeVelocityBecameOutOfSync;
	
	// Either use a fake time that is based on ticks instead of time.
	// or, do an internal timer contained within the class.
	sf::Time m_gameTime;
	SFSpriteComponentPtr m_sprite;
	SFHealthSpriteComponentPtr m_healthSprite;

	bool m_textureIsDirty;
};