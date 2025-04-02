#pragma once
#include "core/component.h"

class Player;

class PlayerComponent : public Component {
	GDCLASS(PlayerComponent, Component);

public:
	PlayerComponent();
	~PlayerComponent();

	Player *get_player() const;
	void set_player(Player *p_player);

	virtual PackedStringArray _get_configuration_warnings() const override;

private:
	void on_actor_changed(Node* prev_actor);

protected:
	static void _bind_methods();
};
