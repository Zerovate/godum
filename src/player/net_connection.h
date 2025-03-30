#pragma once
#include "player.h"

class NetConnection : public Player {
	GDCLASS(NetConnection, Player);

protected:
	static void _bind_methods() {}
};
