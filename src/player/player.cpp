#include "player.h"
#include "player_component.h"

Player::Player() {
	connect("child_entered_tree", Callable(this, "try_add_player_component"));
	connect("child_exiting_tree", Callable(this, "try_erase_player_controller"));
}

Player::~Player() {
	disconnect("child_entered_tree", Callable(this, "try_add_player_component"));
	disconnect("child_exiting_tree", Callable(this, "try_erase_player_controller"));
}

TypedArray<PlayerComponent> Player::get_player_components(const StringName &name) const {
	TypedArray<PlayerComponent> res;
	for (auto idx = 0; idx < m_player_components.size(); idx++) {
		PlayerComponent *ctrl = m_player_components[idx];
		ERR_CONTINUE(!ctrl);
		if (ctrl->is_class(name)) {
			res.append(ctrl);
		}
	}
	return res;
}

bool Player::try_add_player_component(Node *node) {
	ERR_FAIL_COND_V(!node, false);
	PlayerComponent *ctrl = Object::cast_to<PlayerComponent>(node);
	if (ctrl) {
		m_player_components.push_back(ctrl);
		return true;
	}
	return false;
}

bool Player::try_erase_player_controller(Node *node) {
	ERR_FAIL_COND_V(!node, false);
	PlayerComponent *ctrl = Object::cast_to<PlayerComponent>(node);
	if (ctrl) {
		m_player_components.erase(ctrl);
		return true;
	}
	return false;
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player_components", "name"), &Player::get_player_components);
	ClassDB::bind_method(D_METHOD("try_add_player_component", "child"), &Player::try_add_player_component);
	ClassDB::bind_method(D_METHOD("try_erase_player_controller", "child"), &Player::try_erase_player_controller);
}