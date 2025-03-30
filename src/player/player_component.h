#pragma once
#include "engine/component.h"

class Player;

class PlayerComponent : public Component {
	GDCLASS(PlayerComponent, Component);

public:
	PlayerComponent();
	~PlayerComponent();

	Player *get_player() const;

protected:
	void _notification(int p_notification);

	void _on_child_entered_tree(Node *node);
	void _on_child_exiting_tree(Node *node);

	Player *m_player;

protected:
	static void _bind_methods();
};
