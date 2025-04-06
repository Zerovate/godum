#pragma once

#include <godot_cpp/classes/multiplayer_peer.hpp>
using namespace godot;

class SteamMultiplayerPeer : public MultiplayerPeer {
	GDCLASS(SteamMultiplayerPeer, MultiplayerPeer);

public:
	Error create_server(int p_game_port, int p_query_port);

	// virtual bool is_server() const override;
};
