
class InputState
{
public:

	InputState() :
		mDesiredRightAmount(0),
		mDesiredLeftAmount(0),
		mDesiredForwardAmount(0),
		mDesiredBackAmount(0),
		mIsShooting(false)
		{}

	float GetDesiredHorizontalDelta()	const { return mDesiredRightAmount - mDesiredLeftAmount; }
	float GetDesiredVerticalDelta()		const { return mDesiredForwardAmount - mDesiredBackAmount; }
	bool  IsShooting()					const { return mIsShooting; }
	bool  IsShootingRight()				const { return mShootingRight; }
	bool  IsShootingLeft()				const { return mShootingLeft; }
	bool  IsEntered()					const { return mIsEntered; }

	bool Write( OutputMemoryBitStream& inOutputStream ) const;
	bool Read( InputMemoryBitStream& inInputStream );

private:
	friend class InputManager;

	float	mDesiredRightAmount, mDesiredLeftAmount;
	float	mDesiredForwardAmount, mDesiredBackAmount;
	bool	mIsShooting, mIsEntered, mShootingRight, mShootingLeft;
};