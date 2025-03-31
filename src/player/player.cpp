#include "player.h"
#include "player_component.h"

Player::Player() {
}

Player::~Player() {
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
		print_line("Player ", get_name(), " added player component ", pc->get_name());
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
		pc->disconnect("player_changed", Callable(this, "try_erase_player_controller").bind(pc));
		print_line("Player ", get_name(), " erased player component ", pc->get_name());
		return true;
	}
	return false;
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player_components", "name"), &Player::get_player_components);
	ClassDB::bind_method(D_METHOD("try_add_player_component", "node"), &Player::try_add_player_component);
	ClassDB::bind_method(D_METHOD("try_erase_player_controller", "node"), &Player::try_erase_player_controller);
}