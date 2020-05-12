#pragma once
#include <SFML/Network/Packet.hpp>
namespace ServerPacketType
{
	enum class Type
	{
		Welcome,
		State,
		ReplicationData,
		PlayerDisconnect,
		ServerPacketTypeCount
	};
}

namespace ClientPacketType
{
	enum class Type
	{
		Hello,
		Input,
		Disconnect,
		LobbyReady,
		Kill,
		ClientPacketTypeCount
	};
}