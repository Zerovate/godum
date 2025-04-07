#pragma once

#ifdef GODUM_MODULE
#include <scene/main/multiplayer_peer.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/multiplayer_peer.hpp>
using namespace godot;
#endif

class SteamP2PMultiplayerPeer : public MultiplayerPeer {
	GDCLASS(SteamP2PMultiplayerPeer, MultiplayerPeer);

public:
	Error create_server(int p_game_port, int p_query_port);

	// virtual bool is_server() const override;
};
