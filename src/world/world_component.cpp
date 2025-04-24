#include "world_component.h"

#include "world/world_node.h"

WorldComponent::WorldComponent() {
	// only WorldNode2D or WorldNode3D (for node tidy) can be parent.
	m_support_actor_types = { "WorldNode" };
	connect("actor_changed", Callable(this, "on_actor_changed"));
}

WorldComponent::~WorldComponent() {
	disconnect("actor_changed", Callable(this, "on_actor_changed"));
}

WorldNode *WorldComponent::get_world() const {
	return Object::cast_to<WorldNode>(m_actor);
}

void WorldComponent::set_world(WorldNode *world) {
	set_actor(world);
}

void WorldComponent::on_actor_changed(Node *prev_actor, Node *new_actor) {
	WorldNode *prev_world = get_world();
	if (prev_world) {
		prev_world->unregister_component(this);
	}
	WorldNode *new_world = get_world();
	if (new_world) {
		new_world->register_component(this);
	}
	emit_signal("world_changed", prev_world, new_world);
}

PackedStringArray WorldComponent::_get_configuration_warnings() const {
	// PackedStringArray warnings = Component::_get_configuration_warnings();
	PackedStringArray warnings;
	if (!get_world()) {
		warnings.append("WorldComponent is not bind to a WorldNode. Please put WorldComponent as a child of WorldNode.");
	}
	return warnings;
}

void WorldComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_world"), &WorldComponent::get_world);
	ClassDB::bind_method(D_METHOD("set_world", "world"), &WorldComponent::set_world);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world", PROPERTY_HINT_RESOURCE_TYPE, "WorldNode"), "set_world", "get_world");

	ClassDB::bind_method(D_METHOD("on_actor_changed", "prev_actor", "new_actor"), &WorldComponent::on_actor_changed);

	ADD_SIGNAL(MethodInfo("world_changed",
			PropertyInfo(Variant::OBJECT, "prev_world", PROPERTY_HINT_RESOURCE_TYPE, "WorldNode"),
			PropertyInfo(Variant::OBJECT, "new_world", PROPERTY_HINT_RESOURCE_TYPE, "WorldNode")));
}
