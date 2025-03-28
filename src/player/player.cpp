#include "player.h"
#include "player_component.h"

Player::Player() {
	connect("child_entered_tree", Callable(this, "try_add_controller"));
	connect("child_exiting_tree", Callable(this, "try_erase_controller"));
}

Player::~Player() {
	disconnect("child_entered_tree", Callable(this, "try_add_controller"));
	disconnect("child_exiting_tree", Callable(this, "try_erase_controller"));
}

TypedArray<PlayerComponent> Player::get_controllers(const StringName &name) const {
	TypedArray<PlayerComponent> res;
	for (auto idx = 0; idx < controller_list.size(); idx++) {
		auto ctrl = controller_list[idx];
		ERR_CONTINUE(!ctrl);
		if (ctrl->is_class(name)) {
			res.append(ctrl);
		}
	}
	return res;
}

bool Player::try_add_controller(Node *node) {
	ERR_FAIL_COND_V(!node, false);
	PlayerComponent *ctrl = Object::cast_to<PlayerComponent>(node);
	if (ctrl) {
		controller_list.push_back(ctrl);
		return true;
	}
	return false;
}

bool Player::try_erase_controller(Node *node) {
	ERR_FAIL_COND_V(!node, false);
	PlayerComponent *ctrl = Object::cast_to<PlayerComponent>(node);
	if (ctrl) {
		controller_list.erase(ctrl);
		return true;
	}
	return false;
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_controllers", "name"), &Player::get_controllers);
	ClassDB::bind_method(D_METHOD("try_add_controller", "child"), &Player::try_add_controller);
	ClassDB::bind_method(D_METHOD("try_erase_controller", "child"), &Player::try_erase_controller);
}