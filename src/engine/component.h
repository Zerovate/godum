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
	Vector<StringName> m_parent_types_allowed = {};
	Vector<StringName> m_parent_types_not_allowed = {};

	void _notification(int p_what);

private:
	bool _is_parent_type_valid(Node *p_parent) const;

protected:
	static void _bind_methods() {}
};
