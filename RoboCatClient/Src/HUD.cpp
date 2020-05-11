#include <RoboCatClientPCH.h>

std::unique_ptr< HUD >	HUD::sInstance;


HUD::HUD() :
mScoreBoardOrigin( 50.f, 60.f, 0.0f ),
mBandwidthOrigin( 250.f, 10.f, 0.0f ),
mRoundTripTimeOrigin( 50.f, 10.f, 0.0f ),
mScoreOffset( 0.f, 50.f, 0.0f ),
mHealthOffset( 1000, 10.f, 0.0f ),
mHealth( 0 )
{
}


void HUD::StaticInit()
{
	sInstance.reset( new HUD() );
}

void HUD::Render()
{
	RenderBandWidth();
	RenderRoundTripTime();
	RenderScoreBoard();
	RenderHealth();
}

void HUD::RenderHealth()
{
	if( mHealth > 0 )
	{
		string healthString = StringUtils::Sprintf( "Health %d", mHealth );
		RenderText( healthString, mHealthOffset, Colors::Red );
	}
}

void HUD::RenderBandWidth()
{
	string bandwidth = StringUtils::Sprintf( "In %d  Bps, Out %d Bps",
												static_cast< int >( NetworkManagerClient::sInstance->GetBytesReceivedPerSecond().GetValue() ),
												static_cast< int >( NetworkManagerClient::sInstance->GetBytesSentPerSecond().GetValue() ) );
	RenderText( bandwidth, mBandwidthOrigin, Colors::White );
}

void HUD::RenderRoundTripTime()
{
	float rttMS = NetworkManagerClient::sInstance->GetAvgRoundTripTime().GetValue() * 1000.f;

	string roundTripTime = StringUtils::Sprintf( "RTT %d ms", ( int ) rttMS  );
	RenderText( roundTripTime, mRoundTripTimeOrigin, Colors::White );
}

void HUD::RenderScoreBoard()
{
	const vector< ScoreBoardManager::Entry >& entries = ScoreBoardManager::sInstance->GetEntries();
	Vector3 offset = mScoreBoardOrigin;
	
	for( const auto& entry: entries )
	{
		RenderText( entry.GetFormattedNameScore(), offset, entry.GetColor() );
		offset.mX += mScoreOffset.mX;
		offset.mY += mScoreOffset.mY;
	}

}

void HUD::RenderText( const string& inStr, const Vector3& origin, const Vector3& inColor )
{
	
}
