#include "entity_component.h"
#include "entity_manager.h"
#include "entity_proxy.h"

EntityComponent::EntityComponent() {
	connect("actor_changed", Callable(this, "_on_actor_changed"));
	m_unsupport_actor_types = { "Player", "World" };
}
EntityComponent::~EntityComponent() {
	disconnect("actor_changed", Callable(this, "_on_actor_changed"));
}

Node *EntityComponent::get_entity() const {
	return m_actor;
}

void EntityComponent::set_entity(Node *entity) {
	set_actor(entity);
}

EntityProxy *EntityComponent::get_entity_proxy() const {
	if (m_actor) {
		return EntityManager::get_singleton()->get_entity_proxy(m_actor);
	}
	return nullptr;
}

void EntityComponent::_on_actor_changed(Node *prev_actor, Node *new_actor) {
	// register component to actor.
	if (prev_actor) {
		EntityManager::get_singleton()->unregister_component(prev_actor, this);
	}
	if (new_actor) {
		EntityManager::get_singleton()->register_component(new_actor, this);
	}
}

void EntityComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_entity"), &EntityComponent::get_entity);
	ClassDB::bind_method(D_METHOD("set_entity", "entity"), &EntityComponent::set_entity);
	ClassDB::bind_method(D_METHOD("get_entity_proxy"), &EntityComponent::get_entity_proxy);
	ClassDB::bind_method(D_METHOD("_on_actor_changed"), &EntityComponent::_on_actor_changed);
}
