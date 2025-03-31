#include "component.h"

bool _is_owner_type_valid(Node *owner, const Vector<StringName> &allowed, const Vector<StringName> &disallowed) {
	bool is_valid = false;
	print_line("owner type: ", owner->get_class(), ", ", owner->get_name());
	if (!allowed.is_empty()) {
		for (auto type : allowed) {
			print_line("allowed type: ", type);
			if (owner->is_class(type)) {
				return true;
			}
		}
	} else {
		is_valid = true;
	}
	for (auto type : disallowed) {
		if (owner->is_class(type)) {
			ERR_FAIL_V_MSG(false, "Invalid parent type");
		}
	}
	return is_valid;
}

void Component::_notification(int p_what) {
	switch (p_what) {
		case Node::NOTIFICATION_READY: {
			print_line("Component ready: owner_changed signal connected");
			connect("owner_changed", Callable(this, "_on_owner_changed"));
		} break;
		case Node::NOTIFICATION_EXIT_TREE: {
			disconnect("owner_changed", Callable(this, "_on_owner_changed"));
		} break;
		default:
			break;
	}
}

void Component::_on_owner_changed() {
	if (!_is_owner_type_valid(get_owner(), m_allowed_owner_types, m_disallowed_owner_types)) {
		print_line("invalid owner type");
		ERR_PRINT("Invalid owner type");
	}
	on_owner_changed();
}

void Component::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_owner_changed"), &Component::_on_owner_changed);
}
