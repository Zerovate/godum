#include "game_instance.h"
#include "world/world_node.h"

#ifdef GODUM_MODULE
#include "core/object/class_db.h"
#endif

GameInstance *GameInstance::singleton = nullptr;

GameInstance *GameInstance::get_singleton() {
	return singleton;
}

WorldNode *GameInstance::get_world() const {
	return world;
}

void GameInstance::_bind_methods() {
	COMPONENT_HOLDER_BIND_METHODS(GameInstance);
}