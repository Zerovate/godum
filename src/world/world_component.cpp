#include "world_component.h"

WorldComponent::WorldComponent() {
	// only WorldNode2D or WorldNode3D (for node tidy) can be parent.
	m_support_actor_types = { "WorldNode2D", "WorldNode3D" };
}

void WorldComponent::_bind_methods() {
}
