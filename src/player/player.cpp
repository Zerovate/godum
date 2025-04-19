#include "player.h"
#include "entity/entity_proxy.h"

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

	ClassDB::bind_method(D_METHOD("get_pawns"), &Player::get_pawns);
	ClassDB::bind_method(D_METHOD("register_pawn", "pawn"), &Player::register_pawn);
	ClassDB::bind_method(D_METHOD("unregister_pawn", "pawn"), &Player::unregister_pawn);

	ADD_SIGNAL(MethodInfo("pc_binded", PropertyInfo(Variant::OBJECT, "pc", PROPERTY_HINT_RESOURCE_TYPE, "PlayerComponent")));
	ADD_SIGNAL(MethodInfo("pc_unbinded", PropertyInfo(Variant::OBJECT, "pc", PROPERTY_HINT_RESOURCE_TYPE, "PlayerComponent")));
}