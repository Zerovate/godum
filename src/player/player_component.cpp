#include "player_component.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_allowed_actor_types = { "Player" };
	connect("actor_changed", Callable(this, "on_actor_changed"));
}
PlayerComponent::~PlayerComponent() {
	disconnect("actor_changed", Callable(this, "on_actor_changed"));
}

void PlayerComponent::on_actor_changed() {
	emit_signal("player_changed");

	if (m_prev_player) {
		m_prev_player->try_unbind_player_controller(this);
	}
	Player *player = get_player();
	if (player) {
		player->try_bind_player_component(this);
	}
	m_prev_player = player;
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("set_player", "player"), &PlayerComponent::set_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_RESOURCE_TYPE, "Player", PROPERTY_USAGE_NONE), "set_player", "get_player");

	ClassDB::bind_method(D_METHOD("on_actor_changed"), &PlayerComponent::on_actor_changed);

	ADD_SIGNAL(MethodInfo("player_changed"));
}