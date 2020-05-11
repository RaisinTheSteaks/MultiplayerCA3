#include <RoboCatPCH.h>

//zoom hardcoded at 100...if we want to lock players on screen, this could be calculated from zoom
const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

RoboCat::RoboCat() :
	GameObject(),
	mMaxRotationSpeed( 5.f ),
	mMaxLinearSpeed( 5000.f ),
	mVelocity( Vector3::Zero ),
	mWallRestitution( 0.1f ),
	mCatRestitution( 0.1f ),
	mThrustDir( sf::Vector2f(0.f, 0.f) ),
	mPlayerId( 0 ),
	mIsShooting( false ),
	mHealth( 10 )
{
	SetCollisionRadius( 20.f );
}

void RoboCat::ProcessInput( float inDeltaTime, const InputState& inInputState )
{
	//process our input....

	int rot = -1;
	int W = 0;
	int NW = 45;
	int N = 90;
	int NE = 135;
	int E = 180;
	int SE = 225;
	int S = 270;
	int SW = 315;


	//turning...
	//float newRotation = GetRotation() + inInputState.GetDesiredHorizontalDelta() * mMaxRotationSpeed * inDeltaTime;
	//SetRotation( newRotation );
	
	////moving...
	//float inputForwardDelta = inInputState.GetDesiredVerticalDelta();
	//mThrustDir = inputForwardDelta;

	float inputHorizontalDelta = inInputState.GetDesiredHorizontalDelta();
	mThrustDir.x = inputHorizontalDelta;
	float inputForwardDelta = inInputState.GetDesiredVerticalDelta();
	mThrustDir.y = -inputForwardDelta;

	
	if (mThrustDir.x == 1 && mThrustDir.y == 1)
		rot = NE;
	else if (mThrustDir.x == 1 && mThrustDir.y == -1)
		rot = NW;
	else if (mThrustDir.x == -1 && mThrustDir.y == 1)
		rot = SE;
	else if (mThrustDir.x == -1 && mThrustDir.y == -1)
		rot = SW;
	else if (mThrustDir.x == 1 && mThrustDir.y == 0)
		rot = N;
	else if (mThrustDir.x == -1 && mThrustDir.y == 0)
		rot = S;
	else if (mThrustDir.x == 0 && mThrustDir.y == 1)
		rot = E;
	else if (mThrustDir.x == 0 && mThrustDir.y == -1)
		rot = W;
	
	if (rot != -1)
		SetRotation(rot);

	mIsShooting = inInputState.IsShooting();
}

void RoboCat::AdjustVelocityByThrust( float inDeltaTime )
{
	//just set the velocity based on the thrust direction -- no thrust will lead to 0 velocity
	//simulating acceleration makes the client prediction a bit more complex
	Vector3 forwardVector = GetForwardVector();
	//mVelocity = forwardVector * (mThrustDir * inDeltaTime * mMaxLinearSpeed);
	mVelocity = Vector3(GetForwardVector().mX + (mThrustDir.x * inDeltaTime * mMaxLinearSpeed), GetForwardVector().mY + (mThrustDir.y * inDeltaTime * mMaxLinearSpeed), GetForwardVector().mZ);
}

void RoboCat::SimulateMovement( float inDeltaTime )
{
	//simulate us...
	AdjustVelocityByThrust( inDeltaTime );
	
	// Replace with a "TryMove" that preemptively checks for collisions.
	TryMove(mVelocity * inDeltaTime);
	//SetLocation( GetLocation() + mVelocity * inDeltaTime );

	// Will encompass the collisions with everything except the walls.
	ProcessCollisions();
}

void RoboCat::Update()
{
	
}

void RoboCat::TryMove(Vector3 p_move)
{
	// SetLocation() to update location.
	sf::Vector2f move(p_move.mX, p_move.mY);
	
	// Make a collision box in here for the player, square around the player.
	float size = 25;
	// Position at the centre of the player.
	Vector3 playerPosition = GetLocation();
	sf::FloatRect player(playerPosition.mX - (size / 2), playerPosition.mY - (size / 2), size, size);

	player.left += move.x;
	player.top += move.y;

	if (!ShadowFactory::sInstance->doesCollideWithWorld(player))
	{
		SetLocation(playerPosition + p_move);
		return;
	}

	// Move checks for single dimension movement.
	player.top -= move.y;
	if (!ShadowFactory::sInstance->doesCollideWithWorld(player))
	{
		SetLocation(playerPosition + Vector3(p_move.mX, 0, 0));
		return;
	}
	
	player.top += move.y;
	player.left -= move.x;
	if (!ShadowFactory::sInstance->doesCollideWithWorld(player))
	{
		SetLocation(playerPosition + Vector3(0, p_move.mY, 0));
		return;
	}
}

void RoboCat::ProcessCollisions()
{
	//right now just bounce off the sides..
	//ProcessCollisionsWithScreenWalls();

	float sourceRadius = GetCollisionRadius();
	Vector3 sourceLocation = GetLocation();

	//now let's iterate through the world and see what we hit...
	//note: since there's a small number of objects in our game, this is fine.
	//but in a real game, brute-force checking collisions against every other object is not efficient.
	//it would be preferable to use a quad tree or some other structure to minimize the
	//number of collisions that need to be tested.
	for( auto goIt = World::sInstance->GetGameObjects().begin(), end = World::sInstance->GetGameObjects().end(); goIt != end; ++goIt )
	{
		GameObject* target = goIt->get();
		if (target->GetClassId() == 'MOUS')
		{
		}
		if( target != this && !target->DoesWantToDie() )
		{
			//simple collision test for spheres- are the radii summed less than the distance?
			Vector3 targetLocation = target->GetLocation();
			float targetRadius = target->GetCollisionRadius();

			Vector3 delta = targetLocation - sourceLocation;
			float distSq = delta.LengthSq2D();
			float collisionDist = ( sourceRadius + targetRadius );
			if( distSq < ( collisionDist * collisionDist ) )
			{
				//first, tell the other guy there was a collision with a cat, so it can do something...

				if( target->HandleCollisionWithCat( this ) )
				{
					//okay, you hit something!
					//so, project your location far enough that you're not colliding
					Vector3 dirToTarget = delta;
					dirToTarget.Normalize2D();
					Vector3 acceptableDeltaFromSourceToTarget = dirToTarget * collisionDist;
					//important note- we only move this cat. the other cat can take care of moving itself
					SetLocation( targetLocation - acceptableDeltaFromSourceToTarget );

					
					Vector3 relVel = mVelocity;
				
					//if other object is a cat, it might have velocity, so there might be relative velocity...
					RoboCat* targetCat = target->GetAsCat();
					if( targetCat )
					{
						relVel -= targetCat->mVelocity;
					}

					//got vel with dir between objects to figure out if they're moving towards each other
					//and if so, the magnitude of the impulse ( since they're both just balls )
					float relVelDotDir = Dot2D( relVel, dirToTarget );

					if (relVelDotDir > 0.f)
					{
						Vector3 impulse = relVelDotDir * dirToTarget;
					
						if( targetCat )
						{
							mVelocity -= impulse;
							mVelocity *= mCatRestitution;
						}
						else
						{
							mVelocity -= impulse * 2.f;
							mVelocity *= mWallRestitution;
						}
					}
				}
			}
		}
	}

}

uint32_t RoboCat::Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const
{
	uint32_t writtenState = 0;

	if( inDirtyState & ECRS_PlayerId )
	{
		inOutputStream.Write( (bool)true );
		inOutputStream.Write( GetPlayerId() );

		writtenState |= ECRS_PlayerId;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}


	if( inDirtyState & ECRS_Pose )
	{
		inOutputStream.Write( (bool)true );

		Vector3 velocity = mVelocity;
		inOutputStream.Write( velocity.mX );
		inOutputStream.Write( velocity.mY );

		Vector3 location = GetLocation();
		inOutputStream.Write( location.mX );
		inOutputStream.Write( location.mY );

		inOutputStream.Write( GetRotation() );

		writtenState |= ECRS_Pose;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	//always write mThrustDir- it's just two bits
	if( mThrustDir != sf::Vector2f(0.f,0.f))
	{
		inOutputStream.Write( true );
		inOutputStream.Write(mThrustDir.x > 0.f);
		inOutputStream.Write(mThrustDir.y > 0.f);
	}
	else
	{
		inOutputStream.Write( false );
	}

	if( inDirtyState & ECRS_Color )
	{
		inOutputStream.Write( (bool)true );
		inOutputStream.Write( GetColor() );

		writtenState |= ECRS_Color;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	if( inDirtyState & ECRS_Health )
	{
		inOutputStream.Write( (bool)true );
		inOutputStream.Write( mHealth, 4 );

		writtenState |= ECRS_Health;
	}
	else
	{
		inOutputStream.Write( (bool)false );
	}

	return writtenState;
}
