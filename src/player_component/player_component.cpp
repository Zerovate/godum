#include "player_component.h"

#include "player/player.h"
#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_allowed_actor_types = { "Player" };
	connect("actor_changed", Callable(this, "on_actor_changed"));
}
PlayerComponent::~PlayerComponent() {
	disconnect("actor_changed", Callable(this, "on_actor_changed"));
}

Player *PlayerComponent::get_player() const {
	return Object::cast_to<Player>(m_actor);
}
void PlayerComponent::set_player(Player *p_player) {
	set_actor(p_player);
}

void PlayerComponent::on_actor_changed(Node *prev_actor) {
	emit_signal("player_changed");

	Player *prev_player = Object::cast_to<Player>(prev_actor);
	if (prev_player) {
		prev_player->try_unbind_player_controller(this);
	}
	Player *player = get_player();
	if (player) {
		player->try_bind_player_component(this);
	}
	update_configuration_warnings();
}

PackedStringArray PlayerComponent::_get_configuration_warnings() const {
	PackedStringArray warnings = Component::_get_configuration_warnings();
	if (!get_player()) {
		warnings.append("PlayerComponent is not bind to a Player. Please put PlayerComponent as a child of Player.");
	}
	return warnings;
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("set_player", "player"), &PlayerComponent::set_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_RESOURCE_TYPE, "Player", PROPERTY_USAGE_NONE), "set_player", "get_player");

	ClassDB::bind_method(D_METHOD("on_actor_changed"), &PlayerComponent::on_actor_changed);

	ADD_SIGNAL(MethodInfo("player_changed"));
}