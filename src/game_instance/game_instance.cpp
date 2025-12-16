#include "game_instance.h"
#include "../world/world_node.h"

#ifdef GODUM_MODULE
#include "core/object/class_db.h"
#endif

GameInstance *GameInstance::singleton = nullptr;

GameInstance::GameInstance() {
	singleton = this;
}

GameInstance *GameInstance::get_singleton() {
	return singleton;
}

WorldNode *GameInstance::get_world() const {
	return m_world;
}

void GameInstance::set_world(WorldNode *world) {
	m_world = world;
}

void GameInstance::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(GameInstance);

	ClassDB::bind_method(D_METHOD("get_world"), &GameInstance::get_world);
	ClassDB::bind_method(D_METHOD("set_world", "world"), &GameInstance::set_world);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "world", PROPERTY_HINT_RESOURCE_TYPE, "WorldNode"), "set_world", "get_world");
}