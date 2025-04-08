#include "session_gi_component.h"

#ifdef GODUM_MODULE
#include <modules/enet/enet_multiplayer_peer.h>
#include <scene/main/multiplayer_api.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/web_rtc_multiplayer_peer.hpp>
#endif

void SessionGIComponent::_bind_methods() {}

void SessionGIComponent::HostSession(const Ref<HostSessionRequest> &request) {
	Ref<ENetMultiplayerPeer> peer = memnew(ENetMultiplayerPeer);
	// peer->create_server();
	// Ref<WebRTCMultiplayerPeer> peer = memnew(WebRTCMultiplayerPeer);
	// peer->create_server();
	get_multiplayer()->set_multiplayer_peer(peer);
}

void SessionGIComponent::JoinSession() {
}
