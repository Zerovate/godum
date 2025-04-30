#include "entity_proxy.h"
#include "player/player.h"

EntityProxy::EntityProxy(Node *entity) :
		m_entity(entity) {
	DEV_ASSERT(entity);
	if (_try_find_player()) {
		m_player->register_pawn(this);
	}
}

EntityProxy::~EntityProxy() {
	if (m_player) {
		m_player->unregister_pawn(this);
	}
}

Node *EntityProxy::get_entity() const {
	return m_entity;
}

Player *EntityProxy::get_player() const {
	return m_player;
}
void EntityProxy::set_player(Player *player) {
	m_player = player;
}

bool EntityProxy::_try_find_player() {
	Node *parent_node = m_entity->get_parent();
	while (parent_node && !parent_node->is_class("SceneTree")) {
		if (parent_node->is_class("Player")) {
			m_player = Object::cast_to<Player>(parent_node);
			return true;
		}
		parent_node = parent_node->get_parent();
	}
	return false;
}

void EntityProxy::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entity"), &EntityProxy::get_entity);
	ClassDB::bind_method(D_METHOD("get_player"), &EntityProxy::get_player);
	ClassDB::bind_method(D_METHOD("set_player", "player"), &EntityProxy::set_player);
}
