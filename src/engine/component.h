#pragma once
#ifdef GODUM_MODULE
#include <scene/main/node.h>
#endif // GODUM_MODULE

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/node.hpp>
using namespace godot;
#endif // GODUM_GDEXTENSION

class Component : public Node {
	GDCLASS(Component, Node);

protected:
	void set_actor(Node *p_actor);
	Node *get_actor();
	Node *m_actor;

	Vector<StringName> m_allowed_actor_types = {};
	Vector<StringName> m_disallowed_actor_types = {};

private:
	bool _is_actor_type_valid(Node *p_actor);

protected:
	static void _bind_methods();
};
