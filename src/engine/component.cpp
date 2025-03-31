#include "component.h"

bool Component::_is_actor_type_valid(Node *p_actor) {
	// actor must be valid
	if (!p_actor) {
		return false;
	}

	bool is_valid = false;
	// check if actor type is allowed
	if (!m_allowed_actor_types.is_empty()) {
		for (auto type : m_allowed_actor_types) {
			if (p_actor->is_class(type)) {
				return true;
			}
		}
	} else {
		is_valid = true;
	}

	// check if actor type is disallowed
	for (auto type : m_disallowed_actor_types) {
		if (p_actor->is_class(type)) {
			return false;
		}
	}
	return is_valid;
}

void Component::set_actor(Node *p_actor) {
	if (!_is_actor_type_valid(p_actor)) {
		WARN_PRINT("Invalid actor type");
		return;
	}
	if (m_actor != p_actor) {
		m_actor = p_actor;
		emit_signal("actor_changed");
	}
}

Node *Component::get_actor() {
	return m_actor;
}

void Component::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_actor", "actor"), &Component::set_actor);
	ClassDB::bind_method(D_METHOD("get_actor"), &Component::get_actor);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "actor", PROPERTY_HINT_RESOURCE_TYPE, "Node", PROPERTY_USAGE_NONE), "set_actor", "get_actor");

	ADD_SIGNAL(MethodInfo("actor_changed"));
}
