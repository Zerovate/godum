#include "register_types.h"

#ifdef GODUM_MODULE
#include <core/core_bind.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <gdextension_interface.h>

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#endif

#include "steam_connection.h"
#include "steam_multiplayer_peer.h"
#include "steam_packet_peer.h"
#include "steam_peer_config.h"

using namespace godot;

void initialize_steam_multiplayer_peer(ModuleInitializationLevel level) {
	if (level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		ClassDB::register_class<SteamPeerConfig>();
		ClassDB::register_class<SteamPacketPeer>();
		ClassDB::register_class<SteamConnection>();
		ClassDB::register_class<SteamMultiplayerPeer>();
	}
}

void uninitialize_steam_multiplayer_peer(ModuleInitializationLevel level) {
	if (level == MODULE_INITIALIZATION_LEVEL_SCENE) {
	}
}
