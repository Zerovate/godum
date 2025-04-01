#pragma once
#include "player.h"

class NetPlayer : public Player {
	GDCLASS(NetPlayer, Player);

public:
	virtual void set_role(Role role) override;

protected:
	static void _bind_methods() {}
};
