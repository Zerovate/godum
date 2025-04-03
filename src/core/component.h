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

public:
	void set_actor(Node *p_actor);
	Node *get_actor();

public:
	void _enter_tree() override;
	void _exit_tree() override;

protected:
	Node *m_actor = nullptr;

	Vector<StringName> m_allowed_actor_types = {};
	Vector<StringName> m_disallowed_actor_types = {};

private:
	bool _is_actor_type_valid(Node *p_actor);
	Node *_try_find_actor();

protected:
	static void _bind_methods();
};
