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
	virtual void on_owner_changed() {}

	void _notification(int p_what);

	Vector<StringName> m_allowed_owner_types = {};
	Vector<StringName> m_disallowed_owner_types = {};

private:
	void _on_owner_changed();

protected:
	static void _bind_methods();
};
