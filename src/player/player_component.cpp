#include "player_component.h"
#include "player/player.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	connect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	connect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

PlayerComponent::~PlayerComponent() {
	disconnect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	disconnect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

void PlayerComponent::_on_child_entered_tree(Node *p_child) {
	ERR_FAIL_COND_MSG(!m_player, "Player not found");
	m_player->try_add_controller(p_child);
}

void PlayerComponent::_on_child_exiting_tree(Node *p_child) {
	ERR_FAIL_COND_MSG(!m_player, "Player not found");
	m_player->try_erase_controller(p_child);
}

Player *PlayerComponent::get_player() const {
	return m_player;
}

void PlayerComponent::_notification(int p_notification) {
	switch (p_notification) {
		case Node::NOTIFICATION_PARENTED: {
			Node *parent = get_parent();
			if (!_is_parent_type_valid(parent)) {
				if (Engine::get_singleton()->is_editor_hint()) {
					parent->call_deferred("remove_child", this);
				} else {
					queue_free();
				}
			} else {
				if (parent->is_class("Player")) {
					m_player = Object::cast_to<Player>(parent);
				} else {
					m_player = Object::cast_to<Player>(parent->call("get_player"));
				}
				ERR_FAIL_COND_MSG(!m_player, "Player not found");
			}
		} break;
	}
}

bool PlayerComponent::_is_parent_type_valid(Node *p_parent) const {
	for (auto type : m_allowed_parent_type) {
		if (p_parent->is_class(type)) {
			return true;
		}
	}
	ERR_FAIL_V_MSG(false, "Invalid parent type");
	return false;
}

void PlayerComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_player"), &PlayerComponent::get_player);
	ClassDB::bind_method(D_METHOD("_on_child_entered_tree"), &PlayerComponent::_on_child_entered_tree);
	ClassDB::bind_method(D_METHOD("_on_child_exiting_tree"), &PlayerComponent::_on_child_exiting_tree);
}
