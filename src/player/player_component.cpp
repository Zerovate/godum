#include "player_component.h"
#include "player/player.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_parent_types_allowed = { "Player", "PlayerComponent" };
	connect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	connect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

PlayerComponent::~PlayerComponent() {
	disconnect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	disconnect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

void PlayerComponent::_on_child_entered_tree(Node *p_child) {
	ERR_FAIL_COND_MSG(!m_player, "Player not found");
	m_player->try_add_player_component(p_child);
}

void PlayerComponent::_on_child_exiting_tree(Node *p_child) {
	ERR_FAIL_COND_MSG(!m_player, "Player not found");
	m_player->try_erase_player_controller(p_child);
}

Player *PlayerComponent::get_player() const {
	return m_player;
}

void PlayerComponent::_notification(int p_notification) {
	Component::_notification(p_notification);
	switch (p_notification) {
		case Node::NOTIFICATION_PARENTED: {
			Node *parent = get_parent();
			if (parent->is_class("Player")) {
				m_player = Object::cast_to<Player>(parent);
			} else if (parent->is_class("PlayerComponent")) {
				m_player = Object::cast_to<Player>(parent->call("get_player"));
			}
		} break;
	}
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("_on_child_entered_tree"), &PlayerComponent::_on_child_entered_tree);
	ClassDB::bind_method(D_METHOD("_on_child_exiting_tree"), &PlayerComponent::_on_child_exiting_tree);
}
