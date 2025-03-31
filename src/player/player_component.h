#pragma once
#include "engine/component.h"
#include "player.h"

class PlayerComponent : public Component {
	GDCLASS(PlayerComponent, Component);

public:
	PlayerComponent();
	~PlayerComponent();

	_FORCE_INLINE_ Player *get_player() const { return Object::cast_to<Player>(get_owner()); }
	_FORCE_INLINE_ void set_player(Player *p_player) { set_owner(p_player); }

protected:
	void _notification(int p_what);
	virtual void on_owner_changed() override;

	// void _on_child_entered_tree(Node *node);
	// void _on_child_exiting_tree(Node *node);

	Player *m_player;

protected:
	static void _bind_methods();
};
