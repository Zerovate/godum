#include "world_component.h"

#include "world/world_node.h"

WorldComponent::WorldComponent() {
	// only WorldNode2D or WorldNode3D (for node tidy) can be parent.
	m_support_actor_types = { "WorldNode" };
}

WorldNode *WorldComponent::get_world() const {
	return Object::cast_to<WorldNode>(m_actor);
}

void WorldComponent::set_world(WorldNode *world) {
	set_actor(world);
}

void WorldComponent::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_world"), &WorldComponent::get_world);
	ClassDB::bind_method(D_METHOD("set_world", "world"), &WorldComponent::set_world);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world", PROPERTY_HINT_RESOURCE_TYPE, "WorldNode"), "set_world", "get_world");
}
