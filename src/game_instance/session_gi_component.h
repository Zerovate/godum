#pragma once
#include "gi_component.h"

#ifdef GODUM_MODULE
#include <core/io/resource.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/resource.hpp>
using namespace godot;
#endif

enum SessionOnlineMode {
	SESSION_ONLINE_MODE_OFFLINE = 0,
	SESSION_ONLINE_MODE_LAN = 1,
	SESSION_ONLINE_MODE_ONLINE = 2,
};

class HostSessionRequest : public Resource {
	GDCLASS(HostSessionRequest, Resource);

public:
	SessionOnlineMode online_mode;

	bool use_lobby;

	bool use_lobbies_voice_chat;

	int max_peer_count = 16;
};

class SessionGIComponent : public GIComponent {
	GDCLASS(SessionGIComponent, GIComponent);

public:
	void HostSession(const Ref<HostSessionRequest> &request);

	void JoinSession();

protected:
	static void _bind_methods();
};
