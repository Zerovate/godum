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
	Node *get_actor() const;

public:
	void _enter_tree();
	void _exit_tree();

protected:
#ifdef GODUM_MODULE
	void _notification(int p_what);
#endif

	Node *m_actor = nullptr;

	Vector<StringName> m_support_actor_types = {};
	Vector<StringName> m_unsupport_actor_types = {};

	bool m_find_actor_by_tree = true;

private:
	bool _is_actor_type_valid(Node *p_actor);
	Node *_try_find_actor();

protected:
	static void _bind_methods();
};
