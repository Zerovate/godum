#pragma once
#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION

class Player;

class PlayerComponent : public Node {
	GDCLASS(PlayerComponent, Node);

public:
	PlayerComponent();
	~PlayerComponent();

	Player *get_player() const;

protected:
	void _notification(int p_notification);

	void _on_child_entered_tree(Node *node);
	void _on_child_exiting_tree(Node *node);

	Vector<StringName> m_allowed_parent_type = { "Player", "PlayerComponent" };
	Player *m_player;

private:
	bool _is_parent_type_valid(Node *p_parent) const;

protected:
	static void _bind_methods();
};
