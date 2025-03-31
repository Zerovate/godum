#include "player_component.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_allowed_actor_types = { "Player" };
}
PlayerComponent::~PlayerComponent() {
}

void PlayerComponent::_enter_tree() {
	print_line("bind actor_changed");
	connect("actor_changed", Callable(this, "on_actor_changed"));
}

void PlayerComponent::_exit_tree() {
	print_line("exit tree");
	Player *player = get_player();
	if (player) {
		print_line("player erase player component");
		player->try_erase_player_controller(this);
	}
	disconnect("actor_changed", Callable(this, "on_actor_changed"));
}

void PlayerComponent::on_actor_changed() {
	print_line("on_actor_changed");
	Player *player = get_player();
	player->try_add_player_component(this);
	emit_signal("player_changed", player);
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("set_player", "player"), &PlayerComponent::set_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_RESOURCE_TYPE, "Player", PROPERTY_USAGE_NONE), "set_player", "get_player");

	ClassDB::bind_method(D_METHOD("on_actor_changed"), &PlayerComponent::on_actor_changed);

	ADD_SIGNAL(MethodInfo("player_changed"));
}