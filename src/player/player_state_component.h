#pragma once
#include "../player_component/player_component.h"

class PlayerStateComponent : public PlayerComponent {
	GDCLASS(PlayerStateComponent, PlayerComponent);

protected:
	static void _bind_methods() {}
};
