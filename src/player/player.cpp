#include "player.h"

void Player::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(Player);

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

	ADD_SIGNAL(MethodInfo("pc_binded", PropertyInfo(Variant::OBJECT, "pc", PROPERTY_HINT_RESOURCE_TYPE, "PlayerComponent")));
	ADD_SIGNAL(MethodInfo("pc_unbinded", PropertyInfo(Variant::OBJECT, "pc", PROPERTY_HINT_RESOURCE_TYPE, "PlayerComponent")));
}