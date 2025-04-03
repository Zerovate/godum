#include "entity_component.h"
#include "entity_manager.h"

EntityComponent::EntityComponent() {
	connect("actor_changed", Callable(this, "_on_actor_changed"));
}
EntityComponent::~EntityComponent() {
	disconnect("actor_changed", Callable(this, "_on_actor_changed"));
}

void EntityComponent::_on_actor_changed(Node *prev_actor) {
	// dependency injection into actor
	// EntityManager::get_singleton()->register_component(m_actor, this);
}

void EntityComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_actor_changed"), &EntityComponent::_on_actor_changed);
}
