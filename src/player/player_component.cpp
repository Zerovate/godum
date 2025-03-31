#include "player_component.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_allowed_actor_types = { "Player" };
}

Player *_try_find_player(PlayerComponent *p_node) {
	if (!p_node) {
		return nullptr;
	}
	Node *parent_node = p_node->get_parent();
	while (parent_node) {
		if (parent_node->is_class("Player")) {
			return Object::cast_to<Player>(parent_node);
		}
		parent_node = parent_node->get_parent();
	}
	return nullptr;
}

void PlayerComponent::_notification(int p_what) {
	switch (p_what) {
		case Node::NOTIFICATION_READY: {
			connect("actor_changed", Callable(this, "on_actor_changed"));
			Player *player = _try_find_player(this);
			if (player) {
				set_player(player);
			} else {
				WARN_PRINT("PlayerComponent::_notification: Player not found.");
			}
		} break;
		default:
			break;
	}
}

void PlayerComponent::on_actor_changed() {
	Player *player = get_player();
	player->try_add_player_component(this);
	emit_signal("player_changed", player);
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("set_player", "player"), &PlayerComponent::set_player);
	ClassDB::add_property("player", PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_RESOURCE_TYPE, "Player", PROPERTY_USAGE_NONE), "set_player", "get_player");

	ADD_SIGNAL(MethodInfo("player_changed", PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT, "Node")));
}