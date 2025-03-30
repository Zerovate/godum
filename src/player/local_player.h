#pragma once
#include "player.h"

class LocalPlayer : public Player {
	GDCLASS(LocalPlayer, Player);

protected:
	static void _bind_methods() {}
};
