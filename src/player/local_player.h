#pragma once
#include "player.h"

class LocalPlayer : public Player {
	GDCLASS(LocalPlayer, Player);

public:
	LocalPlayer();

	virtual void set_role(Role role) override;

protected:
	static void _bind_methods() {}
};
