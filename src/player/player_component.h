#pragma once
#include "engine/component.h"
#include "player.h"

class PlayerComponent : public Component {
	GDCLASS(PlayerComponent, Component);

public:
	PlayerComponent();

	_FORCE_INLINE_ Player *get_player() const { return Object::cast_to<Player>(m_actor); }
	_FORCE_INLINE_ void set_player(Player *p_player) { set_actor(p_player); }

protected:
	void _notification(int p_what);

private:
	void on_actor_changed();

protected:
	static void _bind_methods();
};
