#include <RoboCatPCH.h>

Mouse::Mouse()
{
	SetScale( GetScale() * 1.f );
	SetCollisionRadius( 20.f );
	picked = false;
}

bool Mouse::HandleCollisionWithCat( RoboCat* inCat )
{
	if (!picked)
	{
//		inCat->GetHealth()++;
//		picked = true;

		SoundManager::sInstance->PlaySound(SoundManager::SoundToPlay::STP_Pickup);
	}
	( void ) inCat;
	return false;
}



uint32_t Mouse::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const 
{
	uint32_t writtenState = 0;

	if( inDirtyState & EMRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= EMRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & EMRS_Color )
	{
		inOutputStream.Write( (bool)true );

		inOutputStream.Write( GetColor() );

		writtenState |= EMRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}


	return writtenState;
}

void Mouse::Read( InputMemoryBitStream& inInputStream )
{
	bool stateBit;

	inInputStream.Read( stateBit );
	if( stateBit )
	{
		Vector3 location;
		inInputStream.Read( location.mX );
		inInputStream.Read( location.mY );
		SetLocation( location );

		float rotation;
		inInputStream.Read( rotation );
		SetRotation( rotation );
	}


	inInputStream.Read( stateBit );
	if( stateBit )
	{	
		Vector3 color;
		inInputStream.Read( color );
		SetColor( color );
	}
}

