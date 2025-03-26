#include "player.h"
#include "engine/controller.h"

TypedArray<Controller> Player::get_controllers(const StringName &name) const {
	TypedArray<Controller> res;
	for (auto idx = 0; idx < controller_list.size(); idx++) {
		auto ctrl = controller_list[idx];
		if (ctrl->get_name() == name) {
			res.append(ctrl);
		}
	}
	return res;
}

void Player::_notification(int p_what) {
	switch (p_what) {
		case Node::NOTIFICATION_READY:
			connect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
			connect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
	}
}

void Player::_on_child_entered_tree(Node *child) {
	Controller *ctrl = Object::cast_to<Controller>(child);
	if (ctrl) {
		controller_list.push_back(ctrl);
	}
}

void Player::_on_child_exiting_tree(Node *child) {
	Controller *ctrl = Object::cast_to<Controller>(child);
	if (ctrl) {
		controller_list.erase(ctrl);
	}
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_controllers", "name"), &Player::get_controllers);
	ClassDB::bind_method(D_METHOD("_on_child_entered_tree", "child"), &Player::_on_child_entered_tree);
	ClassDB::bind_method(D_METHOD("_on_child_exiting_tree", "child"), &Player::_on_child_exiting_tree);
}