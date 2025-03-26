#pragma once

#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION;

class Controller;

class Player : public Node {
	GDCLASS(Player, Node);

public:
	Player();

	TypedArray<Controller> get_controllers(const StringName &name) const;

private:
	Vector<Controller *> controller_list;

	void _on_child_entered_tree(Node *node);
	void _on_child_exiting_tree(Node *node);

protected:
	static void _bind_methods();
};
