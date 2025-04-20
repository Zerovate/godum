#include "component.h"

#ifdef GODUM_MODULE
#include <core/config/engine.h>
#endif

#ifdef GODUM_GDEXTENSION
#include <godot_cpp/classes/engine.hpp>
#endif

void Component::_enter_tree() {
	if (!m_find_actor_by_tree) {
		return;
	}
	Node *actor = _try_find_actor();
	if (!actor) {
		if (Engine::get_singleton()->is_editor_hint()) {
			WARN_PRINT(vformat("Component %s has no actor", get_name()));
		} else {
			CRASH_NOW_MSG(vformat("Component %s has no actor", get_path()));
		}
	} else {
		print_line(vformat("Component %s bind actor %s", get_name(), actor->get_name()));
	}
	set_actor(actor);
}

void Component::_exit_tree() {
	if (!m_find_actor_by_tree) {
		return;
	}
	set_actor(nullptr);
}

#ifdef GODUM_MODULE
void Component::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_enter_tree();
		} break;
		case NOTIFICATION_EXIT_TREE: {
			_exit_tree();
		} break;
	}
}
#endif

void Component::set_actor(Node *p_actor) {
	if (m_actor != p_actor) {
		Node *prev_actor = m_actor;
		m_actor = p_actor;
		emit_signal("actor_changed", prev_actor, p_actor);
	}
}

Node *Component::_try_find_actor() {
	Node *parent_node = this->get_parent();
	while (parent_node) {
		if (_is_actor_type_valid(parent_node)) {
			return parent_node;
		} else if (parent_node->is_class("Component")) {
			parent_node = parent_node->get_parent();
		} else {
			return nullptr;
		}
	}
	return nullptr;
}

Node *Component::get_actor() const {
	return m_actor;
}

bool Component::_is_actor_type_valid(Node *p_actor) {
	// actor must be valid
	if (!p_actor) {
		return false;
	}
	if (p_actor->is_class("Component")) {
		return false;
	}

	bool is_valid = false;
	// check if actor type is allowed
	if (!m_support_actor_types.is_empty()) {
		for (auto type : m_support_actor_types) {
			if (p_actor->is_class(type)) {
				return true;
			}
		}
	} else {
		is_valid = true;
	}

	// check if actor type is disallowed
	for (auto type : m_unsupport_actor_types) {
		if (p_actor->is_class(type)) {
			return false;
		}
	}
	return is_valid;
}

void Component::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_actor", "actor"), &Component::set_actor);
	ClassDB::bind_method(D_METHOD("get_actor"), &Component::get_actor);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "actor", PROPERTY_HINT_RESOURCE_TYPE, "Node", PROPERTY_USAGE_NONE), "set_actor", "get_actor");

	GDVIRTUAL_BIND(type);

	ADD_SIGNAL(MethodInfo("actor_changed",
			PropertyInfo(Variant::OBJECT, "prev_actor", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT, "Node"),
			PropertyInfo(Variant::OBJECT, "new_actor", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT, "Node")));
	ADD_SIGNAL(MethodInfo("registered"));
	ADD_SIGNAL(MethodInfo("unregistered"));
}
