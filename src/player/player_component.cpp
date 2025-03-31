#include "player_component.h"

#include <godot_cpp/classes/engine.hpp>

PlayerComponent::PlayerComponent() {
	// only Player or PlayerComponent (for node tidy) can be parent.
	m_allowed_owner_types.append("Player");
	// connect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	// connect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

PlayerComponent::~PlayerComponent() {
	// disconnect("child_entered_tree", Callable(this, "_on_child_entered_tree"));
	// disconnect("child_exiting_tree", Callable(this, "_on_child_exiting_tree"));
}

Player *_find_player(PlayerComponent *p_node) {
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
			Player *player = _find_player(this);
			if (player) {
				print_line("PlayerComponent ready: find player ", player->get_name());
			}
			set_player(player);
		} break;
		default:
			break;
	}
}

// void PlayerComponent::_on_child_entered_tree(Node *p_child) {
// 	print_line("child entered tree: ", p_child->get_name());
// 	if (m_player) {
// 		m_player->try_add_player_component(p_child);
// 	}
// }

// void PlayerComponent::_on_child_exiting_tree(Node *p_child) {
// 	if (m_player) {
// 		m_player->try_erase_player_controller(p_child);
// 	}
// }

void PlayerComponent::on_owner_changed() {
	Player *new_player = Object::cast_to<Player>(get_owner());
	if (!new_player) {
		WARN_PRINT("PlayerComponent owner is not Player");
		if (m_player) {
			WARN_PRINT("roll back to previous owner");
			set_owner(m_player);
		}
		return;
	}

	print_line(get_name(), " child count: ", get_child_count());
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
	// ClassDB::bind_method(D_METHOD("set_player", "player"), &PlayerComponent::set_player);
	// ClassDB::add_property("PlayerComponent", PropertyInfo(Variant::OBJECT, "player"), "set_player", "get_player");

	// ClassDB::bind_method(D_METHOD("_on_child_entered_tree"), &PlayerComponent::_on_child_entered_tree);
	// ClassDB::bind_method(D_METHOD("_on_child_exiting_tree"), &PlayerComponent::_on_child_exiting_tree);

	ADD_SIGNAL(MethodInfo("player_changed", PropertyInfo(Variant::OBJECT, "player", PROPERTY_HINT_NODE_TYPE, "Player", PROPERTY_USAGE_DEFAULT, "Player")));
}