#include "entity_component.h"
#include "entity_component_manager.h"

EntityComponent::EntityComponent() {
	connect("actor_changed", Callable(this, "_on_actor_changed"));
	m_disallowed_actor_types = { "Player", "World" };
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

void EntityComponent::_on_actor_changed(Node *prev_actor, Node *new_actor) {
	// register component to actor.
	if (prev_actor) {
		ECM::get_singleton()->unregister_component(prev_actor, this);
	}
	if (new_actor) {
		ECM::get_singleton()->register_component(new_actor, this);
	}
}

void EntityComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_actor_changed"), &EntityComponent::_on_actor_changed);
}
