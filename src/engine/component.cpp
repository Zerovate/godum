#include "component.h"

#include <godot_cpp/classes/engine.hpp>

bool Component::_is_parent_type_valid(Node *p_parent) const {
	bool is_valid = false;
	if (!m_parent_types_allowed.is_empty()) {
		for (auto type : m_parent_types_allowed) {
			if (p_parent->is_class(type)) {
				return true;
			}
		}
	} else {
		is_valid = true;
	}
	for (auto type : m_parent_types_not_allowed) {
		if (p_parent->is_class(type)) {
			ERR_FAIL_V_MSG(false, "Invalid parent type");
		}
	}
	return is_valid;
}

void Component::_notification(int p_what) {
	switch (p_what) {
		case Node::NOTIFICATION_PARENTED:
			Node *parent = get_parent();
			if (!_is_parent_type_valid(parent)) {
				if (Engine::get_singleton()->is_editor_hint()) {
					parent->call_deferred("remove_child", this);
				} else {
					queue_free();
				}
			}
	}
}
