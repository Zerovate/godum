#include "world_node.h"
#include "entity_manager_component.h"

WorldNode::WorldNode() {
	EntityManagerComponent *entity_manager_component = memnew(EntityManagerComponent);
	register_component(entity_manager_component);
}

void WorldNode::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(WorldNode);
}
