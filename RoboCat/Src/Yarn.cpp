#include <RoboCatPCH.h>

Yarn::Yarn() :
	mMuzzleSpeed( 400.f ),
	mVelocity( Vector3::Zero ),
	mPlayerId( 0 )
{
	SetScale( GetScale() * .02f );
	SetCollisionRadius( 15.f );
}



uint32_t Yarn::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
{
	uint32_t writtenState = 0;

	if( inDirtyState & EYRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		Vector3 velocity = GetVelocity();
		inOutputStream.Write( velocity.mX );
		inOutputStream.Write( velocity.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= EYRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EYRS_Color )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( GetColor() );

		writtenState |= EYRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EYRS_PlayerId )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( mPlayerId, 8 );

		writtenState |= EYRS_PlayerId;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}




	return writtenState;
}



bool Yarn::HandleCollisionWithCat( RoboCat* inCat )
{
	( void ) inCat;

	//you hit a cat, so look like you hit a cat

	return false;
}

//Kevin
//Rather than using the normalised velocity of the player to get the direction the yarn now 
//finds the direction the player is pointing by using the players rotation.
void Yarn::InitFromShooter( RoboCat* inShooter )
{
	SetColor( inShooter->GetColor() );
	SetPlayerId( inShooter->GetPlayerId() );
	

	Vector3 forward = inShooter->GetForwardVector();
	Vector3 vel = inShooter->GetVelocity();
	auto normVel = thor::unitVector(sf::Vector2f(vel.mX, vel.mY));
	sf::Vector2f temp = sf::Vector2f(0, -1);
	thor::rotate(temp, inShooter->GetRotation());

	//SetVelocity(Vector3(normVel.x, normVel.y, 0) * mMuzzleSpeed);
	
	SetVelocity(Vector3(temp.x, temp.y, 0) * mMuzzleSpeed);
	SetLocation( inShooter->GetLocation() /*+ Vector3(temp.x,temp.y,0) * 0.55f*/ );

	SetRotation( inShooter->GetRotation() );
}

void Yarn::Update()
{
	
	float deltaTime = Timing::sInstance.GetDeltaTime();

	SetLocation( GetLocation() + mVelocity * deltaTime );
	

	//we'll let the cats handle the collisions
}
