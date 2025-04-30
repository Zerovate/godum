#include "player.h"
#include "entity/entity_proxy.h"
#include "input/input_device.h"
#include <scene/main/multiplayer_api.h>

TypedArray<Node> Player::get_pawns() const {
	TypedArray<Node> res;
	for (auto e : m_pawns) {
		res.append(e->get_entity());
	}
	return res;
}

bool Player::register_pawn(EntityProxy *pawn) {
	if (!pawn) {
		return false;
	}
	m_pawns.insert(pawn);
	return true;
}

bool Player::unregister_pawn(EntityProxy *pawn) {
	if (!pawn) {
		return false;
	}
	return m_pawns.erase(pawn);
}

Ref<InputDevice> Player::get_input_device() const {
	return m_input_device;
}

void Player::set_input_device(const Ref<InputDevice> &device) {
	m_input_device = device;
}

void Player::_enter_tree() {
	if (!get_multiplayer().is_null() && (get_multiplayer()->get_unique_id() != get_multiplayer_authority())) {
		m_role = ROLE_Remote;
	} else {
		m_role = ROLE_Local;
	}
}

#ifdef GODUM_MODULE
void Player::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_enter_tree();
		} break;
	}
}
#endif

void Player::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(Player);

	BIND_ENUM_CONSTANT(ROLE_None);
	BIND_ENUM_CONSTANT(ROLE_Local);
	BIND_ENUM_CONSTANT(ROLE_Remote);
	ClassDB::bind_method(D_METHOD("get_role"), &Player::get_role);
	ClassDB::bind_method(D_METHOD("set_role", "role"), &Player::set_role);
	ADD_PROPERTY(
			PropertyInfo(Variant::INT, "role",
					PROPERTY_HINT_ENUM, "None,Local,Remote"),
			"set_role", "get_role");

	ClassDB::bind_method(D_METHOD("get_input_device"), &Player::get_input_device);
	ClassDB::bind_method(D_METHOD("set_input_device", "device"), &Player::set_input_device);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "input_device", PROPERTY_HINT_RESOURCE_TYPE, "InputDevice"), "set_input_device", "get_input_device");

	ClassDB::bind_method(D_METHOD("get_pawns"), &Player::get_pawns);
	ClassDB::bind_method(D_METHOD("register_pawn", "pawn"), &Player::register_pawn);
	ClassDB::bind_method(D_METHOD("unregister_pawn", "pawn"), &Player::unregister_pawn);

	ADD_SIGNAL(MethodInfo("pc_binded", PropertyInfo(Variant::OBJECT, "pc", PROPERTY_HINT_RESOURCE_TYPE, "PlayerComponent")));
	ADD_SIGNAL(MethodInfo("pc_unbinded", PropertyInfo(Variant::OBJECT, "pc", PROPERTY_HINT_RESOURCE_TYPE, "PlayerComponent")));

	ADD_SIGNAL(MethodInfo("input_device_changed"));
}