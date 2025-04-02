#include "entity_component.h"

EntityComponent::EntityComponent() {
	connect("actor_changed", Callable(this, "_on_actor_changed"));
}
EntityComponent::~EntityComponent() {
	disconnect("actor_changed", Callable(this, "_on_actor_changed"));
}

void EntityComponent::_on_actor_changed(Node *prev_actor) {
	// dependency injection into actor
}

void EntityComponent::get_component() {
}

void _unregister_component(Node *actor) {
}

void _register_component(Node *actor, EntityComponent *component) {
	if (!actor->has_method("get_component")) {
		// actor->call<EntityComponent *>("register_component", component);
		Callable(actor->get("register_component")).call(component);
	} else {
		actor->set("register_component", Callable(&EntityComponent::register_component));
	}
}

void EntityComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_on_actor_changed"), &EntityComponent::_on_actor_changed);
}
