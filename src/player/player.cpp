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
	for (auto pc : m_player_components_map[name]) {
		res.append(pc);
	}
	return res;
}

bool Player::try_add_player_component(Node *node) {
	ERR_FAIL_COND_V(!node, false);
	PlayerComponent *pc = Object::cast_to<PlayerComponent>(node);
	if (pc) {
		StringName class_name = pc->get_class();
		while (class_name != StringName("PlayerComponent")) {
			if (!m_player_components_map.has(class_name)) {
				m_player_components_map.insert(class_name, {});
			}
			m_player_components_map[class_name].insert(pc);
			class_name = ClassDB::get_parent_class(class_name);
			ERR_FAIL_COND_V_MSG(class_name.is_empty(), false, "Invalid parent class");
		}
		return true;
	}
	return false;
}

bool Player::try_erase_player_controller(Node *node) {
	ERR_FAIL_COND_V(!node, false);
	PlayerComponent *pc = Object::cast_to<PlayerComponent>(node);
	if (pc) {
		StringName class_name = pc->get_class();
		while (class_name != StringName("PlayerComponent")) {
			m_player_components_map[class_name].erase(pc);
			class_name = ClassDB::get_parent_class(class_name);
			ERR_FAIL_COND_V_MSG(class_name.is_empty(), false, "Invalid parent class");
		}
		return true;
	}
	return false;
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player_components", "name"), &Player::get_player_components);
	ClassDB::bind_method(D_METHOD("try_add_player_component", "child"), &Player::try_add_player_component);
	ClassDB::bind_method(D_METHOD("try_erase_player_controller", "child"), &Player::try_erase_player_controller);
}