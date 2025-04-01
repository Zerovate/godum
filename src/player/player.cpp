#include "player.h"
#include "player_component.h"

TypedArray<PlayerComponent> Player::get_player_components(const StringName &name) const {
	TypedArray<PlayerComponent> res;
	if (m_player_components_map.has(name)) {
		for (auto pc : m_player_components_map[name]) {
			res.append(pc);
		}
	}
	return res;
}

bool Player::try_bind_player_component(PlayerComponent *pc) {
	ERR_FAIL_COND_V(!pc, false);
	StringName class_name = pc->get_class();
	while (class_name != StringName("PlayerComponent")) {
		if (!m_player_components_map.has(class_name)) {
			m_player_components_map.insert(class_name, {});
		}
		m_player_components_map[class_name].insert(pc);
		class_name = ClassDB::get_parent_class(class_name);
		ERR_FAIL_COND_V_MSG(class_name.is_empty(), false, "Invalid parent class");
	}
	print_line(get_name(), " add pc: ", pc->get_name());
	return true;
}

bool Player::try_unbind_player_controller(PlayerComponent *pc) {
	ERR_FAIL_COND_V(!pc, false);
	StringName class_name = pc->get_class();
	while (class_name != StringName("PlayerComponent")) {
		m_player_components_map[class_name].erase(pc);
		class_name = ClassDB::get_parent_class(class_name);
		ERR_FAIL_COND_V_MSG(class_name.is_empty(), false, "Invalid parent class");
	}
	print_line(get_name(), " erase pc: ", pc->get_name());
	return true;
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player_components", "name"), &Player::get_player_components);
	ClassDB::bind_method(D_METHOD("try_bind_player_component", "node"), &Player::try_bind_player_component);
	ClassDB::bind_method(D_METHOD("try_unbind_player_controller", "node"), &Player::try_unbind_player_controller);

	BIND_ENUM_CONSTANT(ROLE_None);
	BIND_ENUM_CONSTANT(ROLE_SimulatedProxy);
	BIND_ENUM_CONSTANT(ROLE_AutonomouseProxy);
	BIND_ENUM_CONSTANT(ROLE_Authority);
	ClassDB::bind_method(D_METHOD("get_role"), &Player::get_role);
	ClassDB::bind_method(D_METHOD("set_role", "role"), &Player::set_role);
	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "role",
					PROPERTY_HINT_ENUM, "None,Simulated Proxy,Autonomous Proxy,Authority",
					PROPERTY_USAGE_NONE),
			"set_role", "get_role");
}