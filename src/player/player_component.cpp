#include "player_component.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_allowed_owner_types.append("Player");
	connect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	connect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

PlayerComponent::~PlayerComponent() {
	disconnect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	disconnect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

void PlayerComponent::_on_child_entered_tree(Node *p_child) {
	if (m_player) {
		m_player->try_add_player_component(p_child);
	}
}

void PlayerComponent::_on_child_exiting_tree(Node *p_child) {
	if (m_player) {
		m_player->try_erase_player_controller(p_child);
	}
}

void PlayerComponent::on_owner_changed() {
	m_player = Object::cast_to<Player>(get_owner());
	if (!m_player) {
		WARN_PRINT("PlayerComponent owner is not Player");
	}

	for (int i = 0; i < get_child_count(); i++) {
		PlayerComponent *child = Object::cast_to<PlayerComponent>(get_child(i));
		if (child) {
			child->set_player(m_player);
		}
	}
	if (m_player) {
		m_player->try_add_player_component(this);
	}
	emit_signal("player_changed", m_player);
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("set_player", "player"), &PlayerComponent::set_player);
	ClassDB::add_property("PlayerComponent", PropertyInfo(Variant::OBJECT, "player"), "set_player", "get_player");

	ClassDB::bind_method(D_METHOD("_on_child_entered_tree"), &PlayerComponent::_on_child_entered_tree);
	ClassDB::bind_method(D_METHOD("_on_child_exiting_tree"), &PlayerComponent::_on_child_exiting_tree);

	ADD_SIGNAL(MethodInfo("player_changed", PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_NODE_TYPE, "Player", PROPERTY_USAGE_DEFAULT, "Player")));
}